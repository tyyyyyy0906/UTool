#include <QApplication>
#include <QXmlStreamWriter>
#include <QGraphicsDropShadowEffect>
#include <QAbstractButton>
#include <QPainter>
#include <QBitmap>

#if defined(Q_OS_WIN32)
#include <io.h>
#include <windows.h>
#include <setupapi.h>
#include <regstr.h>
#include <winbase.h>
#include <winnls.h>
#include <dbt.h>
#endif

#include "iconhelper.h"
#include "hsaemessagebox.h"
#include "maskwidget.h"
#include "hsaeencrypttool.h"
#include "ui_hsaeencrypttool.h"

#include <openssl/aes.h>
#include <openssl/ssl.h>

#define MSG_LEN 1024
#define clientVersion "HONDA-release"
#define COMPARE_VERSION "HS-V7630W_V9999_20201231"

static const QString honda_version[] = {
    "HS-V7630_V4001-20200901"
};

class HsaeEnCryptTool_
{
public:
    QFont font_;
    QStringList m_deviceInfo;
    QVector<diskList_> m_diskList;
    QVector<QString> vector_;
    QMap<QString, DeviceInfo> diskMap;

    static void setButtonTip(QAbstractButton* buttons,
                             const QString& content = QString(""),
                             const int duration = 3000) {
        if (buttons == nullptr) return;
        buttons->setToolTip(content);
        buttons->setToolTipDuration(duration);
    }
};

HsaeEncryptTool::HsaeEncryptTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HsaeEncryptTool),
    p_(new HsaeEnCryptTool_),
    messager(new NotifyManager)
{
    ui->setupUi(this);

    this->initWindowStyle();

    HsaeMessageBox* uMsc = new HsaeMessageBox;

    connect(ui->minWindow,   SIGNAL(clicked()),        this, SLOT(onMinWindow()));
    connect(ui->closeWindow, SIGNAL(clicked()),        this, SLOT(onCloseWindow()));
    connect(ui->sureExec,    SIGNAL(clicked()),        this, SLOT(onSureExec()));
    connect(this,            SIGNAL(diskAction(bool)), uMsc, SLOT(answerSignal(bool)));
}

HsaeEncryptTool::~HsaeEncryptTool()
{
    delete ui;
    delete p_;
    delete messager;
}

void HsaeEncryptTool::initMoveableDevice()
{
    p_->m_diskList.clear();
    char diskPath[5] = { 0 };
    DWORD allDisk = GetLogicalDrives();         //返回一个32位整数，转成二进制后用于表示磁盘，最低位为A盘。
    if (allDisk != 0)
    {
        for (int i = 0; i < 26; i++)
        {
            if ((allDisk & 1) == 1)
            {
                sprintf(diskPath, "%c", 'A' + i);
                strcat(diskPath, ":");
                LPCWSTR RootPathName = (LPCWSTR)QString(diskPath).utf16();

                if (GetDriveType(RootPathName) ==  DRIVE_REMOVABLE)
                {
                    diskList_ m_disk;
                    QString currPath(diskPath);

                    m_disk.currentPath = currPath;
                    m_disk.isCheck     = true;

                    if(GetVolumeInformation(RootPathName, 0, 0, 0, 0, 0, 0, 0)) //判断当前移动设备驱动是否准备就绪
                    {
                        m_disk.isRead = true;
                        messager->notify("新消息", "检测到了U盘，重新接入一下吧(^▽^ )");
                    }
                    else
                    {
                        m_disk.isRead = false;
                        messager->notify("新消息", "USB设备驱动安装失败了，重新接入一下吧(^▽^ )");
                    }

                    p_->m_diskList.append(m_disk);
                }
            }
         allDisk = allDisk >> 1;
        }
    }

    this->registerDevice();
}

void HsaeEncryptTool::initWindowStyle()
{
    QFile file(":/psblack.css");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        this->setPalette(QPalette(QColor(paletteColor)));
        this->setStyleSheet(qss);
        file.close();
    }

    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint);

    MaskWidget::Instance()->setMainWidget(this);
    QStringList dialogNames;

    dialogNames << "msg";

    MaskWidget::Instance()->setDialogNames(dialogNames);

    IconHelper::Instance()->setIcon(ui->labIco     , QChar(0xf0c7), 16);
    IconHelper::Instance()->setIcon(ui->minWindow  , QChar(0xf068));
    IconHelper::Instance()->setIcon(ui->closeWindow, QChar(0xf00d));

    ui->labTitle->setText("HSAE优盘加密工具");

    p_->font_.setPointSize(10);
    ui->labTitle->setFont(p_->font_);

    ui->sureExec->setText(tr("执行"));
    ui->sureExec->setFont(p_->font_);

    ui->versionLab->setText(clientVersion);
    ui->versionLab->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
    p_->font_.setPointSize(9);
    ui->versionLab->setStyleSheet("QLabel { color: 'white' }");
    ui->versionLab->setFont(p_->font_);

    p_->setButtonTip(ui->minWindow  , tr("最小化") , 5000);
    p_->setButtonTip(ui->closeWindow, tr("关闭")   , 5000);
    p_->setButtonTip(ui->sureExec   , tr("执行加密"), 5000);

    QBitmap bmp(this->size());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 10, 10);
    setMask(bmp);

    this->setWindowFlags(Qt::FramelessWindowHint);

    messager->notify("驿站小管家", "欢迎光临，发现我的都是小可爱呢(๑￫ܫ￩)");

    this->initMoveableDevice();
}

bool HsaeEncryptTool::nativeEvent(const QByteArray & eventType, void * message, long*result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if(msgType == WM_DEVICECHANGE)
    {
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam)
        {
        case DBT_DEVICEARRIVAL:
            qDebug() << "widget::" << lpdb->dbch_devicetype;
            if(DBT_DEVTYP_VOLUME == lpdb->dbch_devicetype)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if (0 == lpdbv->dbcv_flags)
                {
                    DeviceInfo deviceInfo;
                    QString currDisk = QString(this->firstDriveFromMask(lpdbv ->dbcv_unitmask));

                    if(p_->m_deviceInfo.count() >=6)
                    {

                        deviceInfo.deviceInformation(p_->m_deviceInfo.at(1), p_->m_deviceInfo.at(0), currDisk,
                                                     p_->m_deviceInfo.at(4), p_->m_deviceInfo.at(5),
                                                     p_->m_deviceInfo.at(2), p_->m_deviceInfo.at(3));
                    }

                    p_->diskMap.insert(currDisk, deviceInfo);

                    this->addRemoveBox(currDisk, ADD);
                    messager->notify("驿站小管家", "发现U盘一枚哦( ╯▽╰)");
                }
                if (DBTF_MEDIA == lpdbv->dbcv_flags)
                {

                }
            }
            if (DBT_DEVTYP_DEVICEINTERFACE == lpdb->dbch_devicetype)
            {
                PDEV_BROADCAST_DEVICEINTERFACE lpdev = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;
                QString strName = QString::fromWCharArray(lpdev->dbcc_name);

                if(!strName.isEmpty() && strName.length() > 10)
                {
                    if(strName.contains("USBSTOR"))
                    {
                        QStringList listAll = strName.split('#');
                        QStringList listInfo = listAll.at(1).split('&');
                        p_->m_deviceInfo.append(listInfo.at(1).mid(4)); //制造商
                        p_->m_deviceInfo.append(listInfo.at(2).mid(5)); //型号
                        p_->m_deviceInfo.append(listInfo.at(3).mid(4)); //版本
                    }
                    else
                    {
                        p_->m_deviceInfo.clear();
                        QStringList listAll = strName.split('#');
                        QStringList listID = listAll.at(1).split('&');
                        p_->m_deviceInfo.append(listID.at(0).right(4));  //vid
                        p_->m_deviceInfo.append(listID.at(1).right(4));  //pid
                        p_->m_deviceInfo.append(listAll.at(2));          //serial
                    }
                }
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            switch (lpdb->dbch_devicetype)
            {
            case DBT_DEVTYP_VOLUME:
                {
                    PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                    if(lpdbv->dbcv_flags == 0)
                    {
                        QString diskPath = QString(this->firstDriveFromMask(lpdbv ->dbcv_unitmask));

                        if(p_->diskMap.contains(diskPath))
                        {
                            p_->diskMap.remove(diskPath);
                        }

                        this->addRemoveBox(diskPath, REMOVE);
                        messager->notify("驿站小管家", "哎呀，快抓住有一枚U盘跑了呢(/▽＼)");
                    }
                }
                break;
            default:
                break;
            }
            break;
        case DBT_DEVNODES_CHANGED:
            break;
        default:
            break;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}

char HsaeEncryptTool::firstDriveFromMask(quint32 unitmask)
{
    char i;
    for (i = 0; i < 26; ++i)
    {
        if (unitmask & 0x1) break;
        unitmask = unitmask >> 1;
    }
    return (i + 'A');
}

void HsaeEncryptTool::registerDevice()
{
    const GUID GUID_DEVINTERFACE_LIST[] = {
        { 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },
        { 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } }
    };

    HDEVNOTIFY hDevNotify;
    DEV_BROADCAST_DEVICEINTERFACE NotifacationFiler;
    ZeroMemory(&NotifacationFiler, sizeof(DEV_BROADCAST_DEVICEINTERFACE));
    NotifacationFiler.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotifacationFiler.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

    for(size_t i = 0; i < sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID); i++)
    {
        NotifacationFiler.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];

        hDevNotify = RegisterDeviceNotification((HANDLE)this->winId(), &NotifacationFiler, DEVICE_NOTIFY_WINDOW_HANDLE);
        if(!hDevNotify)
        {
            qDebug() << "注册失败!";
        }
    }
}

void HsaeEncryptTool::addRemoveBox(QString disk, int action)
{
    switch (action)
    {
    case HsaeEncryptTool::ADD:
    {
        if(!this->searchDisk(disk))
        {
            p_->vector_.push_back(disk);
            ui->diskComBox->addItem(disk);
        }
        else return;
    }
    break;
    case HsaeEncryptTool::REMOVE:
    {
        if(this->searchDisk(disk))
        {
            for (int i = 0; i < p_->vector_.size(); ++i)
            {
                if (p_->vector_.at(i) == disk)
                {
                    p_->vector_.remove(i);
                    ui->diskComBox->removeItem(ui->diskComBox->findText(disk));
                }
            }
        }
        else return;
    }
    break;
    default: break;
    }
}

bool HsaeEncryptTool::searchDisk(QString diskName)
{
    for(int i = 0; i < p_->vector_.size(); i++)
    {
        if(p_->vector_.at(i) == diskName)
        {
            return true;
        }
    }
    return false;
}

QString HsaeEncryptTool::acquireMd52Version(const QString& path)
{
    QFile file(path);
    if (file.exists())
    {
        if (!filePropety(path))
        {
            SetFileAttributes(reinterpret_cast<const wchar_t *>(path.utf16()), FILE_ATTRIBUTE_READONLY);
        }
        if (!file.open(QIODevice::ReadOnly))
        {
            messager->notify("驿站小管家", "有个config文件过期了呢(┬＿┬)");
            return "";
        }
        else
        {
            QString dealContent;
            while(!file.atEnd())
            {
                QByteArray line = file.readLine();
                QString str(line);
                dealContent.append(str);
            }
            return dealContent.replace("\n", "");
        }

        file.close();
    }
    else
    {
        messager->notify("驿站小管家", "没有找到想要的东西config呢(┬＿┬)");
        return "";
    }
    return QString("");
}

void HsaeEncryptTool::autoCreateXml()
{
    if (QFile::exists(ui->diskComBox->currentText() + ":/update"))
    {
        if (p_->diskMap.contains(ui->diskComBox->currentText()))
        {
            QMap<QString, DeviceInfo>::iterator it = p_->diskMap.find(ui->diskComBox->currentText());

            QFile file(ui->diskComBox->currentText() + ":/update/update.xml");
            file.open(QIODevice::WriteOnly);

            QXmlStreamWriter stream(&file);
            stream.setAutoFormatting(true);
            stream.writeStartDocument();
            stream.writeStartElement("data");

            stream.writeStartElement("PC_CLIENT_VERSION");
            stream.writeAttribute("value", clientVersion);
            stream.writeEndElement();

            stream.writeStartElement("USB_NOTCHECK");
            stream.writeAttribute("value", "false");
            stream.writeEndElement();

            stream.writeStartElement("USB_PID");
            stream.writeAttribute("value", it.value().getDeviceIdPendor());
            stream.writeEndElement();

            stream.writeStartElement("USB_VID");
            stream.writeAttribute("value", it.value().getDeviceIdVendor());
            stream.writeEndElement();

            stream.writeStartElement("USB_SERIAL");
            stream.writeAttribute("value", it.value().getDeviceSerial());
            stream.writeEndElement();

            stream.writeStartElement("USB_PRODUCT");
            stream.writeAttribute("value", it.value().getDeviceType());
            stream.writeEndElement();

            stream.writeStartElement("USB_MANUFACTURER");
            stream.writeAttribute("value", it.value().getDeviceManufacturer());
            stream.writeEndElement();

            stream.writeStartElement("PACKET_MD5");
            stream.writeAttribute("value", acquireMd52Version(QString(ui->diskComBox->currentText() + ":/update/update.md5")));
            stream.writeEndElement();

            stream.writeStartElement("SOFTWARE_VERSION");
            stream.writeAttribute("value", /*acquireMd52Version(QString(ui->diskComBox->currentText() + ":/update/version"))*/COMPARE_VERSION);
            stream.writeEndElement();

            stream.writeEndDocument();
            file.close();

            this->aesEncryption();
        }
    }
    else
    {
        messager->notify("驿站小管家", "没有找到update目录，迷失了呢(┬＿┬)");
        return;
    }
}

void HsaeEncryptTool::aesEncryption()
{
    QByteArray buffer;
    QString encryptContent;

    QFile file(ui->diskComBox->currentText() + ":/update/update.xml");
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while(!file.atEnd())
            {
                buffer = file.readAll();
                encryptContent.append(buffer);
            }
        }
    }
    else
    {
        messager->notify("驿站小管家", "好像没有发现update.xml这件法宝呢(┬＿┬)");
    }

    unsigned char noEncryptCode[MSG_LEN];
    unsigned char isEncryptCode[MSG_LEN];

    memset((unsigned char*)noEncryptCode, 0x00, MSG_LEN);
    strcpy((char*)noEncryptCode, encryptContent.toLatin1().constData());

    this->aes_box_encrypt(noEncryptCode, isEncryptCode);

    QByteArray isEncryptArray((char*)isEncryptCode, MSG_LEN);

    QFile filePath(ui->diskComBox->currentText() + ":/update/update.xml");
    filePath.open(QIODevice::WriteOnly);
    filePath.write(isEncryptArray);
    filePath.close();

    messager->notify("驿站小管家", "太棒啦！加密成功哦o(*￣▽￣*)o");
}

bool HsaeEncryptTool::filePropety(const QString& path)
{
    DWORD pro = GetFileAttributes(reinterpret_cast<const wchar_t *>(path.utf16()));
    if (pro & FILE_ATTRIBUTE_READONLY)
    {
        return true;
    }
    else return false;
}

void HsaeEncryptTool::aes_box_encrypt(unsigned char *source_string, unsigned char *des_string)
{
    AES_KEY aes;
    unsigned char key[AES_BLOCK_SIZE] = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4', '5', '6'
    };
    unsigned char iv[AES_BLOCK_SIZE] = {
        'H', 'S', 'A', 'E', 'W', 'U', 'H', 'A', 'N', 'J', 'I', 'S', 'H', 'U', 'Z', 'X'
    };

    if (NULL == source_string || NULL == des_string) return;
    if (AES_set_encrypt_key(key, 128, &aes) < 0) return ;

    AES_cbc_encrypt(source_string, des_string, 1024, &aes, iv, AES_ENCRYPT);
}

void HsaeEncryptTool::onMinWindow()
{
    this->showMinimized();
}

void HsaeEncryptTool::onCloseWindow()
{
    this->close();
}

void HsaeEncryptTool::onSureExec()
{
    if (ui->diskComBox->currentIndex() == 0)
    {
        messager->notify("驿站小管家", "让我猜猜你想干什么(°ー°〃)");
        return;
    }
    this->autoCreateXml();
}
