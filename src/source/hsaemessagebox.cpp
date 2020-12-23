#include <QFile>
#include <QBitmap>

#include "iconhelper.h"
#include "appinit.h"
#include "hsaemessagebox.h"
#include "ui_hsaemessagebox.h"

HsaeMessageBox *HsaeMessageBox::self = nullptr;
HsaeMessageBox *HsaeMessageBox::Instance()
{
    if (!self)
    {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!self) {
            self = new HsaeMessageBox;
        }
    }
    return self;
}

HsaeMessageBox::HsaeMessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsaeMessageBox)
{
    ui->setupUi(this);

    this->initForm();

    connect(ui->messageClose, SIGNAL(clicked(bool)), this, SLOT(on_MessageBox_clicked()));
    connect(ui->closeBtn,     SIGNAL(clicked(bool)), this, SLOT(on_CloseBtn_clicked()));
}

HsaeMessageBox::~HsaeMessageBox()
{
    delete ui;
}

void HsaeMessageBox::initForm()
{
    QFont font;
    font.setPointSize(10);
    this->setProperty("nav", "top");
    this->setProperty("canMove", false);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool |
                         Qt::WindowStaysOnTopHint);

    IconHelper::Instance()->setIcon(ui->labIcon, QChar(0xf0c7), 16);
    IconHelper::Instance()->setIcon(ui->messageClose, QChar(0xf00d));

    QFile file(":/flatwhite.css");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        this->setPalette(QPalette(QColor(paletteColor)));
        this->setStyleSheet(qss);
        file.close();
    }
    font.setPointSize(12);
    ui->contentText->setFont(font);
    this->setButtonTip(ui->messageClose, "关闭", 5000);
    this->setButtonTip(ui->closeBtn    , "关闭", 5000);

    QBitmap bmp(this->size());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 10, 10);
    setMask(bmp);
}

void HsaeMessageBox::messageBoxShow(QString title, QString contentText, bool messageBtn)
{
    ui->labTitle->setText(title);
    ui->contentText->setText(contentText);
    ui->closeBtn->setVisible(messageBtn);
    this->show();
}

void HsaeMessageBox::on_MessageBox_clicked()
{
    this->close();
}

void HsaeMessageBox::on_CloseBtn_clicked()
{
    this->close();
}

void HsaeMessageBox::answerSignal(bool show)
{
    if(show)
    {
        ui->labTitle->setText("提示");
        ui->contentText->setText("检测到可以移动磁盘插入！");
        ui->closeBtn->setVisible(false);
        this->show();
    }
    else
    {
        this->close();
    }
}

void HsaeMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() + releasePos);
}

void HsaeMessageBox::mousePressEvent(QMouseEvent *event)
{
    releasePos = this->pos() - event->globalPos();
}

void HsaeMessageBox::setButtonTip(QAbstractButton *buttons, const QString &content, const int duration)
{
    if (buttons == nullptr) return;
    buttons->setToolTip(content);
    buttons->setToolTipDuration(duration);
}
