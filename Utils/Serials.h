#pragma once
#include "../Includes/xor.h"

namespace Cleaner
{
    namespace HWID
    {
        void FixupHWIDSerials()
        {
            HANDLE hDevice = CreateFileW(_(L"\\\\.\\PhysicalDrive0").decrypt(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

            if (hDevice == INVALID_HANDLE_VALUE)
                return;

            STORAGE_PROPERTY_QUERY query = {};
            query.PropertyId = StorageDeviceProperty;
            query.QueryType = PropertyStandardQuery;

            BYTE buffer[512] = {};
            DWORD bytesReturned = 0;

            if (DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY, &query, sizeof(query), buffer, sizeof(buffer), &bytesReturned, NULL))
            {
                STORAGE_DEVICE_DESCRIPTOR* descriptor = (STORAGE_DEVICE_DESCRIPTOR*)buffer;
                if (descriptor && descriptor->SerialNumberOffset && descriptor + descriptor->SerialNumberOffset)
                {
                    char* serial = (char*)buffer + descriptor->SerialNumberOffset;
                    if (serial)
                    {
                        try
                        {
                            std::string serialnum = serial;
                            if (!serialnum.empty())
                            {
                                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                                std::wstring serialnumW = converter.from_bytes(serialnum);

                                // this will always match HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 3\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0
                                Registry::SetString(HKEY_LOCAL_MACHINE, _(L"HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 3\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0").decrypt(), _(L"SerialNumber").decrypt(), serialnumW);
                            }
                        }
                        catch (...) {};
                    }
                }
            }
        }
    }
}