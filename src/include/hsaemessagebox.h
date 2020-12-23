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
