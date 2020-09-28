#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>

namespace Ui {
class HMessageBox;
}

class HMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit HMessageBox(QWidget *parent = nullptr);
    ~HMessageBox();

public:
    void initForm();
    //void boxShow(QString &text, )

private:
    Ui::HMessageBox *ui;
};

#endif // MESSAGEBOX_H
