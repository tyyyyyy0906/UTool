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

#ifndef NOTIFY_H
#define NOTIFY_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>

class Notify : public QWidget
{
    Q_OBJECT
public:
    explicit Notify(int displayTime, QWidget *parent = 0);

    void setIcon(const QString &value);
    void setTitle(const QString &value);
    void setBody(const QString &value);
    void setUrl(const QString &value);
    void showGriant();

Q_SIGNALS:
    void disappeared();

private:

    int displayTime;
    QString icon;
    QString title;
    QString body;
    QString url;
    QLabel *backgroundLabel;
    QLabel *iconLabel;
    QLabel *titleLabel;
    QLabel *bodyLabel;
    QPushButton *closeBtn;

    void hideGriant();
    void mousePressEvent(QMouseEvent *event);
};

#endif // NOTIFY_H
