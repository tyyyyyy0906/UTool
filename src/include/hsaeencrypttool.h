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

#ifndef HSAEENCRYPTTOOL_H
#define HSAEENCRYPTTOOL_H

#include <QWidget>
#include <QMainWindow>
#include <QVector>
#include <QMap>

#include "deviceinfo.h"
#include "notifymanager.h"

namespace Ui {
class HsaeEncryptTool;
}

//用于存储当前可移动设备是否准备好了。
typedef struct diskList
{
    QString currentPath;
    bool isRead;
    bool isCheck;
}diskList_;

class HsaeEnCryptTool_;

class HsaeEncryptTool : public QMainWindow
{
    Q_OBJECT

public:
    enum EM_Action
    {
        ADD,
        REMOVE
    };
    Q_ENUM(EM_Action)

public:
    explicit HsaeEncryptTool(QWidget *parent = nullptr);
    ~HsaeEncryptTool();

public:
    void initWindowStyle();         //加载Window样式表
    void initMoveableDevice();      //初始化移动设备检测
    void registerDevice();
    void addRemoveBox(QString disk, int action);
    void autoCreateXml();
    void aesEncryption();
    bool searchDisk(QString diskName);
    char firstDriveFromMask(quint32 unitmask);
    QString acquireMd52Version(const QString& path);
    bool filePropety(const QString& path);

    void aes_box_encrypt(unsigned char* source_string, unsigned char* des_string);

protected:
    bool nativeEvent(const QByteArray & eventType, void * message, long*result);

private slots:
    void onMinWindow();                 //最小动作
    void onCloseWindow();               //关闭动作
    void onSureExec();                  //执行动作
//    void onInfoDisk();

signals:
    void diskAction(bool actionU);

private:
    Ui::HsaeEncryptTool *ui;
    HsaeEnCryptTool_* p_;
    NotifyManager* messager;
};

#endif // HSAEENCRYPTTOOL_H
