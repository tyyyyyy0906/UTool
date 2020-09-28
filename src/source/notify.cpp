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

#include <QPropertyAnimation>
#include <QTimer>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QFontMetrics>
#include <QDesktopServices>
#include <QApplication>

#include "notify.h"

Notify::Notify (int displayTime, QWidget *parent) : QWidget(parent),
    displayTime(displayTime)
{

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint| Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);

    backgroundLabel = new QLabel(this);
    backgroundLabel->move(0, 0);
    backgroundLabel->setObjectName("notify-background");


    QHBoxLayout *mainLayout = new QHBoxLayout(backgroundLabel);
    QVBoxLayout *contentLayout = new QVBoxLayout();

    iconLabel = new QLabel(backgroundLabel);
    iconLabel->setFixedWidth(40);
    iconLabel->setAlignment(Qt::AlignCenter);

    titleLabel = new QLabel(backgroundLabel);
    titleLabel->setObjectName("notify-title");

    bodyLabel = new QLabel(backgroundLabel);
    bodyLabel->setObjectName("notify-body");
    QFont font = bodyLabel->font();
    font.setPixelSize(8);
    bodyLabel->setFont(font);

    contentLayout->addWidget(titleLabel);
    contentLayout->addWidget(bodyLabel);

    mainLayout->addWidget(iconLabel);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(contentLayout);


    closeBtn = new QPushButton("×", backgroundLabel);
    closeBtn->setObjectName("notify-close-btn");
    closeBtn->setFixedSize(16, 16);
    connect(closeBtn, &QPushButton::clicked, this, [this]
    {
        Q_EMIT disappeared();
    });
}


void Notify::showGriant()
{
    this->show();

    titleLabel->setText(title);
    titleLabel->setFont(QFont("微软雅黑"));
    QPixmap tempPix = QPixmap(this->icon);
    tempPix = tempPix.scaled(QSize(30, 30), Qt::KeepAspectRatio);
    iconLabel->setPixmap(tempPix);

    backgroundLabel->setFixedSize(this->size());
    closeBtn->move(backgroundLabel->width() - closeBtn->width() - 5, 5);

    // 超过长度省略号
    QFontMetrics elidfont(bodyLabel->font());
    QString text = elidfont.elidedText(this->body, Qt::ElideRight, bodyLabel->width() - 5);
    bodyLabel->setText(text);
    bodyLabel->setFont(QFont("微软雅黑"));

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity", this);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(200);
    animation->start();

    connect(animation, &QPropertyAnimation::finished, this, [animation, this]()
    {
        animation->deleteLater();
        QTimer::singleShot(displayTime, this, [this]()
        {
            this->hideGriant();
        });
    });
    this->setStyleSheet(
        "#notify-background {"
            "border: 1px solid #fff;"
            "background: #444444;"
            "border-radius: 10px;"
        "} "
        "#notify-title {"
            "font-weight: bold;"
            "color: white;"
            "font-size: 14px;"
        "}"
        "#notify-body {"
            "color: white;"
            "font-size: 12px;"
        "}"
        "#notify-close-btn { "
            "border: 0;"
            "color: white;"
        "}"
        "#notify-close-btn:hover { "
            "background: #444444;"
        "}"
    );
}

void Notify::hideGriant()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity", this);
    animation->setStartValue(this->windowOpacity());
    animation->setEndValue(0);
    animation->setDuration(200);
    animation->start();

    connect(animation, &QPropertyAnimation::finished, this, [animation, this]()
    {
        this->hide();
        animation->deleteLater();
        Q_EMIT disappeared();
    });
}

void Notify::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!url.isEmpty())
        {
            QDesktopServices::openUrl(url);
        }
        hideGriant();
    }
}

void Notify::setUrl(const QString &value)
{
    url = value;
}


void Notify::setBody(const QString &value)
{
    body = value;
}

void Notify::setTitle(const QString &value)
{
    title = value;
}

void Notify::setIcon(const QString &value)
{
    icon = value;
}
