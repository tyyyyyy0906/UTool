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
