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
