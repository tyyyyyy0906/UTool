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

#ifndef HSAEMESSAGEBOX_H
#define HSAEMESSAGEBOX_H

#include <QWidget>
#include <QPoint>
#include <QAbstractButton>

namespace Ui {
class HsaeMessageBox;
}

class HsaeMessageBox : public QWidget
{
    Q_OBJECT

public:
    static HsaeMessageBox *Instance();
    explicit HsaeMessageBox(QWidget *parent = nullptr);
    ~HsaeMessageBox();

public:
    void initForm();
    void messageBoxShow(QString title, QString contentText, bool messageBtn);

private slots:
    void on_MessageBox_clicked();
    void on_CloseBtn_clicked();
    void answerSignal(bool show);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);


private:
    void setButtonTip(QAbstractButton* buttons,
                      const QString& content = QString(""),
                      const int duration = 3000);
private:
    Ui::HsaeMessageBox *ui;
    QPoint releasePos;
    static HsaeMessageBox *self;
};

#endif // HSAEMESSAGEBOX_H
