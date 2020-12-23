#include "deviceinfo.h"

DeviceInfo::DeviceInfo()
{
    deviceIdPendor = deviceIdVendor = deviceDriveLetter  =
    deviceVersion  = deviceSerial   = deviceManufacturer =
    deviceType = "";
}

void DeviceInfo::deviceInformation(
        const QString& deviceIdPendor,
        const QString& deviceIdVendor,
        const QString& deviceDriveLetter,
        const QString& deviceType,
        const QString& deviceVersion,
        const QString& deviceSerial,
        const QString& deviceManufacturer)
{
    this->deviceIdPendor     = deviceIdPendor;
    this->deviceIdVendor     = deviceIdVendor;
    this->deviceDriveLetter  = deviceDriveLetter;
    this->deviceType         = deviceType;
    this->deviceVersion      = deviceVersion;
    this->deviceSerial       = deviceSerial;
    this->deviceManufacturer = deviceManufacturer;
}

QString DeviceInfo::getDeviceIdPendor() const
{
    return this->deviceIdPendor;
}

QString DeviceInfo::getDeviceIdVendor() const
{
    return this->deviceIdVendor;
}

QString DeviceInfo::getDeviceDriveLetter() const
{
    return this->deviceDriveLetter;
}

QString DeviceInfo::getDeviceType() const
{
    return this->deviceType;
}

QString DeviceInfo::getDeviceVersion() const
{
    return this->deviceVersion;
}

QString DeviceInfo::getDeviceSerial() const
{
    return this->deviceSerial;
}

QString DeviceInfo::getDeviceManufacturer() const
{
    return this->deviceManufacturer;
}
