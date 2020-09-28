#include "messagebox.h"
#include "ui_messagebox.h"
#include "iconhelper.h"

#include <QFile>
#include <QMutex>
#include <QMutexLocker>

HMessageBox::HMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HMessageBox)
{
    ui->setupUi(this);

    this->initForm();
}

HMessageBox::~HMessageBox()
{
    delete ui;
}

void HMessageBox::initForm()
{
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        this->setPalette(QPalette(QColor(paletteColor)));
        this->setStyleSheet(qss);
        file.close();
    }

    IconHelper::Instance()->setIcon(ui->labIcon, QChar(0xf0c7), 16);
}
