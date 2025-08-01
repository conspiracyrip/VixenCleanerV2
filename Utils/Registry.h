#pragma once


namespace Registry
{

    bool SetValue(HKEY hRootKey, std::wstring subKeyPath, std::wstring valueName, BYTE* data, DWORD dataSize, DWORD type)
    {
        HKEY hKey;
        if (RegCreateKeyExW(hRootKey, subKeyPath.c_str(), 0, nullptr, 0, KEY_SET_VALUE, nullptr, &hKey, nullptr) != ERROR_SUCCESS)
        {
            //printf("fail, why? %d!\r\n", GetLastError());
            return false;
        }

        LONG result = RegSetValueExW(hKey, valueName.c_str(), 0, type, data, dataSize);
        RegCloseKey(hKey);

        return result == ERROR_SUCCESS;
    }

    bool SetString(HKEY hRootKey, std::wstring subKeyPath, std::wstring valueName, std::wstring data)
    {
        return SetValue(hRootKey, subKeyPath, valueName, (BYTE*)data.c_str(), (data.size() + 1) * sizeof(wchar_t), REG_SZ);
    }

    bool SetDWORD(HKEY hRootKey, std::wstring subKeyPath, std::wstring valueName, DWORD data)
    {
        return SetValue(hRootKey, subKeyPath, valueName, (BYTE*)&data, sizeof(DWORD), REG_DWORD);
    }

    bool SetQWORD(HKEY hRootKey, std::wstring subKeyPath, std::wstring valueName, ULONGLONG data)
    {
        return SetValue(hRootKey, subKeyPath, valueName, (BYTE*)&data, sizeof(ULONGLONG), REG_QWORD);
    }

    bool SetBinary(HKEY hRootKey, std::wstring subKeyPath, std::wstring valueName, BYTE* data, size_t size)
    {
        return SetValue(hRootKey, subKeyPath, valueName, data, size, REG_BINARY);
    }

    bool DeleteValue(HKEY hRootKey, std::wstring subKeyPath, const std::wstring valueName)
    {
        HKEY hKey;
        if (RegOpenKeyExW(hRootKey, subKeyPath.c_str(), 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS)
            return false;

        LONG result = RegDeleteValueW(hKey, valueName.c_str());
        RegCloseKey(hKey);
        return result == ERROR_SUCCESS;
    }

    bool DeleteKey(HKEY hRootKey, std::wstring subKeyPath)
    {
        return RegDeleteKeyW(hRootKey, subKeyPath.c_str()) == ERROR_SUCCESS;
    }

    VOID RecursiveDelete(LPWSTR dir, LPWSTR match);

#define ForEachFile(dir, callback) { \
	WIN32_FIND_DATA fd = { 0 }; \
	HANDLE f = FindFirstFile(dir, &fd); \
	do { \
		if (wcscmp(fd.cFileName, L".") && wcscmp(fd.cFileName, L"..")) { \
			LPWSTR file = fd.cFileName; \
			callback; \
		} \
	} while (FindNextFile(f, &fd)); \
	FindClose(f); \
}

#define ForEachSubkey(hkey_key, callback) { \
	WCHAR name[MAX_PATH] = { 0 }; \
	for (DWORD _i = 0, _s = sizeof(name); ERROR_SUCCESS == RegEnumKeyEx(hkey_key, _i, name, &_s, 0, 0, 0, 0); ++_i, _s = sizeof(name)) { \
		callback; \
	} \
}

    static WCHAR alphabet[] = L"abcdef012345789";


    BOOL AdjustCurrentPrivilege(LPCWSTR privilege) {
        LUID luid = { 0 };
        if (!LookupPrivilegeValue(0, privilege, &luid)) {
            return FALSE;
        }

        TOKEN_PRIVILEGES tp = { 0 };
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        HANDLE token = 0;
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token)) {
            return FALSE;
        }

        if (!AdjustTokenPrivileges(token, FALSE, &tp, sizeof(tp), 0, 0)) {
            CloseHandle(token);
            return FALSE;
        }

        if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
            CloseHandle(token);
            return FALSE;
        }

        CloseHandle(token);
        return TRUE;
    }

    LPWSTR GetKeyPath(HKEY key)
    {
        typedef NTSTATUS(WINAPI* NTQK)(HANDLE KeyHandle, DWORD KeyInformationClass, PVOID KeyInformation, ULONG Length, PULONG ResultLength);
        NTQK NtQueryKey;

        srand(GetTickCount());
        LoadLibraryW(L"ntdll.dll");

        NtQueryKey = (NTQK)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQueryKey");
        if (!AdjustCurrentPrivilege(SE_TAKE_OWNERSHIP_NAME)) {
            //printf("failed to adjust privilege\n");
        }

        static WCHAR buffer[MAX_PATH] = { 0 };
        DWORD size = sizeof(buffer);
        memset(buffer, 0, sizeof(buffer));
        NtQueryKey(key, 3, buffer, size, &size);
        return buffer + 3;
    }

    VOID OutSpoofUnique(LPWSTR buffer) {
        for (DWORD i = 0; i < wcslen(buffer); ++i) {
            if (iswxdigit(buffer[i])) {
                buffer[i] = alphabet[rand() % wcslen(alphabet)];
            }
        }
    }



    BOOL GetKeyValue(HKEY key, LPCWSTR value, LPBYTE buffer, DWORD* size) {
        if (ERROR_SUCCESS == RegQueryValueEx(key, value, 0, 0, buffer, size)) {
            return TRUE;
        }

        // printf("Failed to read: %ws\\%ws\n\n", GetKeyPath(key), value);
        return FALSE;
    }


    VOID KeySpoofOutGUID(HKEY key, LPCWSTR value, LPWSTR buffer, DWORD size) {
        if (!GetKeyValue(key, value, (LPBYTE)buffer, &size)) {
            return;
        }


        OutSpoofUnique(buffer);

        RegSetValueEx(key, value, 0, REG_SZ, (PBYTE)buffer, size);
    }

    VOID KeySpoofUnique(HKEY key, LPCWSTR value) {
        WCHAR buffer[MAX_PATH] = { 0 };
        KeySpoofOutGUID(key, value, buffer, sizeof(buffer));
    }

#define OpenThen(hkey_key, lpcwstr_subkey, callback) { \
	HKEY _k = 0; \
	if (ERROR_SUCCESS != RegOpenKeyEx(hkey_key, lpcwstr_subkey, 0, KEY_ALL_ACCESS, &_k)) { \
	} else { \
		HKEY key = _k; \
		callback; \
		RegCloseKey(key); \
	} \
}

    void SpoofUnique(HKEY key, LPCWSTR subkey, LPCWSTR value) 
    {
        HKEY _k = 0; if (0L != RegOpenKeyExW(key, subkey, 0, (((0x001F0000L) | (0x0001) | (0x0002) | (0x0004) | (0x0008) | (0x0010) | (0x0020)) & (~(0x00100000L))), &_k)) {
        }
        else {
            HKEY key = _k; {
                KeySpoofUnique(key, value);
            }; RegCloseKey(key);
        }
    }

    void SpoofQWORD(HKEY key, LPCWSTR subkey, LPCWSTR value)
    {

        HKEY _k = 0; if (0L != RegOpenKeyExW(key, subkey, 0, (((0x001F0000L) | (0x0001) | (0x0002) | (0x0004) | (0x0008) | (0x0010) | (0x0020)) & (~(0x00100000L))), &_k)) {
        }
        else {
            HKEY key = _k; {
                LARGE_INTEGER data = { 0 }; data.LowPart = rand(); data.HighPart = rand(); if (0L == RegSetValueExW(key, value, 0, (11ul), (PBYTE)&data, sizeof(data))) {
                }
                else {
                }
            }; RegCloseKey(key);
        }
    }

    void SpoofBinary(HKEY key, LPCWSTR subkey, LPCWSTR value)
    {
        {
            HKEY _k = 0;
            
            if (RegOpenKeyExW(key, subkey, 0, (((0x001F0000L) | (0x0001) | (0x0002) | (0x0004) | (0x0008) | (0x0010) | (0x0020)) & (~(0x00100000L))), &_k) != 0)
            {
                printf("Failed to open key: %ws\r\n", subkey);
            }
            else {
                HKEY key = _k;
                {
                    DWORD size = 0; 
                    
                    if (RegQueryValueExW(key, value, 0, 0, 0, &size) != 0) 
                    {
                        RegCloseKey(key); 


                        return;
                    } 
                    
                    BYTE* buffer = (BYTE*)malloc(size); 
                    if (!buffer) 
                    {
                        RegCloseKey(key); return;
                    } 
                    
                    DWORD ogsize = size;
                    
                    for (DWORD i = 0; i < size; ++i)
                    {
                        buffer[i] = (BYTE)(rand() % 0x100);
                    } 


                    SetLastError(0);
                    auto res = RegSetValueExW(key, value, 0, (3ul), buffer, size);
                    //printf("spoofbin res = %d - size: %d - ogsize = %d - getlasterror: %d!\r\n", res, ogsize, size, GetLastError());

                    free(buffer);

                }; 
                
                RegCloseKey(key);
            }
        };
    }
};