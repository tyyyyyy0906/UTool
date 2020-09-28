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

#ifndef MASKWIDGET_H
#define MASKWIDGET_H

#include <QWidget>
#include <QMutex>

class MaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MaskWidget(QWidget *parent = 0);
    static MaskWidget *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new MaskWidget;
            }
        }

        return self;
    }

protected:
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    static MaskWidget *self;
    QWidget *mainWidget;        //需要遮罩的主窗体
    QStringList dialogNames;    //可能弹窗的窗体对象名称集合链表

public slots:
    void setMainWidget(QWidget *mainWidget);
    void setDialogNames(const QStringList &dialogNames);
    void setBgColor(const QColor &bgColor);
    void setOpacity(double opacity);
};

#endif // MASKWIDGET_H
