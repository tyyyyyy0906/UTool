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

#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QString>

class DeviceInfo
{
public:
    DeviceInfo();

    QString getDeviceIdPendor() const;
    QString getDeviceIdVendor() const;
    QString getDeviceDriveLetter() const;
    QString getDeviceType() const;
    QString getDeviceVersion() const;
    QString getDeviceSerial() const;
    QString getDeviceManufacturer() const;
public:
    //接收传入的U盘属性
    void deviceInformation(
            const QString& deviceIdPendor,
            const QString& deviceIdVendor,
            const QString& deviceDriveLetter,
            const QString& deviceType,
            const QString& deviceVersion,
            const QString& deviceSerial,
            const QString& deviceManufacturer);
private:
    //deviceInformation
    QString deviceIdPendor;     //设备Pid
    QString deviceIdVendor;     //设备Vid
    QString deviceDriveLetter;  //设备盘符
    QString deviceType;         //设备类型
    QString deviceVersion;      //设备版本
    QString deviceSerial;       //设备序列号
    QString deviceManufacturer; //设备制造商
};
#endif // DEVICEINFO_H
