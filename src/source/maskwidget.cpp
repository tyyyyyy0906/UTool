/*****************************************************************************
MIT License

Copyright (c) 2020 tyyyyyy0906

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include "maskwidget.h"
#include "qapplication.h"

MaskWidget *MaskWidget::self = 0;
MaskWidget::MaskWidget(QWidget *parent) : QWidget(parent)
{
    mainWidget = 0;
    setOpacity(0.7);
    setBgColor(QColor(0, 0, 0));

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    qApp->installEventFilter(this);
}

void MaskWidget::setMainWidget(QWidget *mainWidget)
{
    if (this->mainWidget != mainWidget){
        this->mainWidget = mainWidget;
    }
}

void MaskWidget::setDialogNames(const QStringList &dialogNames)
{
    if (this->dialogNames != dialogNames){
        this->dialogNames = dialogNames;
    }
}

void MaskWidget::setOpacity(double opacity)
{
    this->setWindowOpacity(opacity);
}

void MaskWidget::setBgColor(const QColor &bgColor)
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, bgColor);
    this->setPalette(palette);
}

void MaskWidget::showEvent(QShowEvent *)
{
    if (mainWidget != 0) {
        this->setGeometry(mainWidget->geometry());
    }
}

bool MaskWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Show)
    {
        if (dialogNames.contains(obj->objectName()))
        {
            this->show();
        }
    }
    else if (event->type() == QEvent::Hide)
    {
        if (dialogNames.contains(obj->objectName()))
        {
            this->hide();
        }
    }

    return QObject::eventFilter(obj, event);
}
