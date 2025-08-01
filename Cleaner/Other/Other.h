#pragma once

#include <stdio.h>
#include <shlwapi.h>
#include <stdio.h>
#include <windows.h>
#include <shlwapi.h>
#include <accctrl.h>
#include <aclapi.h>
#include <shlobj_core.h>
#include <tlhelp32.h>

#pragma comment(lib, "shlwapi.lib")

typedef struct _SECTOR {
	LPCSTR Name;
	DWORD  NameOffset;	
	DWORD  SerialOffset;
} SECTOR, * PSECTOR;

static SECTOR SECTORS[] = {
	{ "FAT",   0x36, 0x27 },
	{ "FAT32", 0x52, 0x43 },
	{ "NTFS",  0x03, 0x48 },
};

#define LENGTH(a) (sizeof(a) / sizeof(a[0]))

namespace Cleaner
{
	namespace Other
	{

		// even more scuffed asf
		void TryDeleteOnDrive(std::wstring Path, std::wstring DriveLetter)
		{
			try
			{
				std::wstring FinalPath = L"";
				if (Path.starts_with(L":")) // handle given like :\\Windows and \Windows or just Windows
					FinalPath = DriveLetter + Path; // given :\\Windows
				else if (Path.starts_with(L"\\"))
					FinalPath = DriveLetter + L":" + Path; // we were given like \Windows
				else
					FinalPath = DriveLetter + L":\\" + Path; // given directly Windows

				if (std::filesystem::exists(FinalPath))
				{
					std::filesystem::remove(FinalPath);
				}
			}
			catch (...) {};
		}

		// even more scuffed asf
		void TryDeleteRecursiveOnDrive(std::wstring Path, std::wstring DriveLetter)
		{
			try
			{
				std::wstring FinalPath = L"";
				if (Path.starts_with(L":")) // handle given like :\\Windows and \Windows or just Windows
					FinalPath = DriveLetter + Path; // given :\\Windows
				else if (Path.starts_with(L"\\"))
					FinalPath = DriveLetter + L":" + Path; // we were given like \Windows
				else
					FinalPath = DriveLetter + L":\\" + Path; // given directly Windows

				if (std::filesystem::exists(FinalPath))
				{
					std::filesystem::remove(FinalPath);
				}
			}
			catch (...) {};
		}

		void TryDeleteItemOnAllDrives(std::wstring PathNoPrefix, bool Directory = true)
		{
			// scuffed asf
			if (Directory)
			{
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"A");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"B");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"C");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"D");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"E");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"F");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"G");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"H");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"I");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"J");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"K");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"L");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"M");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"N");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"O");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"P");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"Q");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"R");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"S");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"T");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"U");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"V");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"W");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"X");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"Y");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"Z");
			}
			else
			{
				TryDeleteOnDrive(PathNoPrefix, L"A");
				TryDeleteOnDrive(PathNoPrefix, L"B");
				TryDeleteOnDrive(PathNoPrefix, L"C");
				TryDeleteOnDrive(PathNoPrefix, L"D");
				TryDeleteOnDrive(PathNoPrefix, L"E");
				TryDeleteOnDrive(PathNoPrefix, L"F");
				TryDeleteOnDrive(PathNoPrefix, L"G");
				TryDeleteOnDrive(PathNoPrefix, L"H");
				TryDeleteOnDrive(PathNoPrefix, L"I");
				TryDeleteOnDrive(PathNoPrefix, L"J");
				TryDeleteOnDrive(PathNoPrefix, L"K");
				TryDeleteOnDrive(PathNoPrefix, L"L");
				TryDeleteOnDrive(PathNoPrefix, L"M");
				TryDeleteOnDrive(PathNoPrefix, L"N");
				TryDeleteOnDrive(PathNoPrefix, L"O");
				TryDeleteOnDrive(PathNoPrefix, L"P");
				TryDeleteOnDrive(PathNoPrefix, L"Q");
				TryDeleteOnDrive(PathNoPrefix, L"R");
				TryDeleteOnDrive(PathNoPrefix, L"S");
				TryDeleteOnDrive(PathNoPrefix, L"T");
				TryDeleteOnDrive(PathNoPrefix, L"U");
				TryDeleteOnDrive(PathNoPrefix, L"V");
				TryDeleteOnDrive(PathNoPrefix, L"W");
				TryDeleteOnDrive(PathNoPrefix, L"X");
				TryDeleteOnDrive(PathNoPrefix, L"Y");
				TryDeleteOnDrive(PathNoPrefix, L"Z");
			}
		}

		std::wstring GetCurrentUsername()
		{
#ifndef UNLEN
#define UNLEN 256	
#endif

			wchar_t username[UNLEN + 1];
			DWORD username_len = UNLEN + 1;
			GetUserNameW(username, &username_len);

			return std::wstring(username);
		}

		void TryDeleteItemOnAllDrivesCurrentUser(std::wstring ArgPath, bool Directory = true)
		{
			std::wstring PathTemp = ArgPath;
			if (!ArgPath.starts_with(L"\\")) // ensure whether its slash start or not itll work.
				PathTemp = L"\\" + ArgPath;

			std::wstring PathNoPrefix = L":\\Users\\" + GetCurrentUsername() + PathTemp;

			// scuffed asf
			if (Directory)
			{
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"A");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"B");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"C");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"D");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"E");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"F");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"G");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"H");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"I");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"J");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"K");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"L");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"M");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"N");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"O");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"P");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"Q");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"R");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"S");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"T");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"U");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"V");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"W");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"X");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"Y");
				TryDeleteRecursiveOnDrive(PathNoPrefix, L"Z");
			}
			else
			{
				TryDeleteOnDrive(PathNoPrefix, L"A");
				TryDeleteOnDrive(PathNoPrefix, L"B");
				TryDeleteOnDrive(PathNoPrefix, L"C");
				TryDeleteOnDrive(PathNoPrefix, L"D");
				TryDeleteOnDrive(PathNoPrefix, L"E");
				TryDeleteOnDrive(PathNoPrefix, L"F");
				TryDeleteOnDrive(PathNoPrefix, L"G");
				TryDeleteOnDrive(PathNoPrefix, L"H");
				TryDeleteOnDrive(PathNoPrefix, L"I");
				TryDeleteOnDrive(PathNoPrefix, L"J");
				TryDeleteOnDrive(PathNoPrefix, L"K");
				TryDeleteOnDrive(PathNoPrefix, L"L");
				TryDeleteOnDrive(PathNoPrefix, L"M");
				TryDeleteOnDrive(PathNoPrefix, L"N");
				TryDeleteOnDrive(PathNoPrefix, L"O");
				TryDeleteOnDrive(PathNoPrefix, L"P");
				TryDeleteOnDrive(PathNoPrefix, L"Q");
				TryDeleteOnDrive(PathNoPrefix, L"R");
				TryDeleteOnDrive(PathNoPrefix, L"S");
				TryDeleteOnDrive(PathNoPrefix, L"T");
				TryDeleteOnDrive(PathNoPrefix, L"U");
				TryDeleteOnDrive(PathNoPrefix, L"V");
				TryDeleteOnDrive(PathNoPrefix, L"W");
				TryDeleteOnDrive(PathNoPrefix, L"X");
				TryDeleteOnDrive(PathNoPrefix, L"Y");
				TryDeleteOnDrive(PathNoPrefix, L"Z");
			}
		}

		bool ReplaceEDIDs() 
		{
			static constexpr LPCWSTR DISPLAY_PATH =
				L"SYSTEM\\CurrentControlSet\\Enum\\DISPLAY";
			HKEY hDisplay = NULL;
			if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, DISPLAY_PATH, 0,
				KEY_READ | KEY_WRITE, &hDisplay) != ERROR_SUCCESS)
				return false;

			for (DWORD monIdx = 0; ; ++monIdx) {
				wchar_t monitorKey[256];
				DWORD monLen = _countof(monitorKey);
				if (RegEnumKeyExW(hDisplay, monIdx, monitorKey, &monLen,
					NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
					break;

				HKEY hMonitor = NULL;
				if (RegOpenKeyExW(hDisplay, monitorKey, 0,
					KEY_READ | KEY_WRITE, &hMonitor) != ERROR_SUCCESS)
					continue;

				for (DWORD instIdx = 0; ; ++instIdx)
			{
					wchar_t instanceKey[256];
					DWORD instLen = _countof(instanceKey);
					if (RegEnumKeyExW(hMonitor, instIdx, instanceKey, &instLen,
						NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
						break;

					HKEY hInst = NULL;
					if (RegOpenKeyExW(hMonitor, instanceKey, 0,
						KEY_READ | KEY_WRITE, &hInst) != ERROR_SUCCESS)
						continue;

					HKEY hParams = NULL;
					if (RegOpenKeyExW(hInst, L"Device Parameters", 0,
						KEY_ALL_ACCESS, &hParams) == ERROR_SUCCESS) {
						DWORD type = 0, dataSize = 0;
						if (RegQueryValueExW(hParams, L"EDID", NULL, &type,
							NULL, &dataSize) == ERROR_SUCCESS
							&& type == REG_BINARY) {
							std::vector<BYTE> newEdid(dataSize);
							std::generate(newEdid.begin(), newEdid.end(), []() { return static_cast<BYTE>(rand() % 256); });

							if (RegSetValueExW(hParams, L"EDID", 0, REG_BINARY,
								newEdid.data(), dataSize) == ERROR_SUCCESS) {
								RegFlushKey(hParams);
							}
						}
						RegCloseKey(hParams);
					}

					RegCloseKey(hInst);
				}

				RegCloseKey(hMonitor);
			}

			RegCloseKey(hDisplay);
			return true;
		}



		void ChangeEDIDLocal_EacDoesntTocuhThisImJustDoingItForFunny()
		{
			try
			{
				ReplaceEDIDs();
			}
			catch (...)
			{

			};
		}

		void CleanupNetwork()
		{
			system(_("net stop browser /y >nul 2>&1").decrypt()); // what

			system(_("IPCONFIG /FLUSHDNS >nul 2>&1").decrypt());
			//system(_("IPCONFIG /RELEASE >nul 2>&1").decrypt());
			//system(_("IPCONFIG /RENEW >nul 2>&1").decrypt());
			system(_("arp -a >nul 2>&1").decrypt());
			system(_("arp -d >nul 2>&1").decrypt());
			system(_("wmic path Win32_PNPEntity where \"caption like \'%bluetooth%\' AND DeviceID like \'USB\\\\%\'\" call disable >nul 2>&1").decrypt());
		}

		bool CleanOtherMisc()
		{
			try
			{
				Cleaner::Other::CleanupNetwork();
			}
			catch (...) {};

			try
			{
				Cleaner::Other::ChangeEDIDLocal_EacDoesntTocuhThisImJustDoingItForFunny();
			}
			catch (...) {};

			try
			{
				Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Diagnostics\\DiagTrack\\SettingsRequests").decrypt());
				Registry::DeleteValue(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\NVIDIA Corporation\\Installer2").decrypt(), _(L"SystemID").decrypt());
				Registry::DeleteValue(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\NVIDIA Corporation\\Global\\CoProcManager").decrypt(), _(L"ChipsetMatchID").decrypt());

				// delete non-existent.
				Registry::DeleteValue(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0000").decrypt(), _(L"HwProfileGuid").decrypt()); // this shouldn't exist!
				Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0002").decrypt());  // this shouldn't exist!
				Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0003").decrypt());  // this shouldn't exist!
				Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0004").decrypt());  // this shouldn't exist!
				Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0005").decrypt());  // this shouldn't exist!
				Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0006").decrypt());  // this shouldn't exist!
				Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0007").decrypt());  // this shouldn't exist!
				Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0008").decrypt());  // this shouldn't exist!
				Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0009").decrypt());  // this shouldn't exist!
			}
			catch (...) {};

			try
			{


				auto temp = std::filesystem::temp_directory_path();

				auto localAppDataPath = temp.parent_path();
				auto AppDataPath = temp.parent_path();

				auto LocalAppDataPathStr = localAppDataPath.string();
				auto AppDataPathStr = AppDataPath.string();

				std::string EpicGamesLocalAppData = "";
				std::string EpicGamesAppData = "";

				std::string FortniteLocalAppData = "";

				if (LocalAppDataPathStr.ends_with("\\"))
					EpicGamesLocalAppData = (LocalAppDataPathStr + "EpicGames");
				else
					EpicGamesLocalAppData = (LocalAppDataPathStr + "\\EpicGames");

				if (AppDataPathStr.ends_with("\\"))
					EpicGamesAppData = (AppDataPathStr + "EpicGames");
				else
					EpicGamesAppData = (AppDataPathStr + "\\EpicGames");

				if (LocalAppDataPathStr.ends_with("\\"))
					FortniteLocalAppData = (LocalAppDataPathStr + "Fortnite");
				else
					FortniteLocalAppData = (LocalAppDataPathStr + "\\Fortnite");


				try
				{
					std::filesystem::remove(FortniteLocalAppData);
					std::filesystem::remove_all(FortniteLocalAppData);
				}
				catch (...) {};


				try
				{
					std::filesystem::remove(EpicGamesLocalAppData);
					std::filesystem::remove_all(EpicGamesLocalAppData);
				}
				catch (...) {};

				try
				{
					std::filesystem::remove((EpicGamesLocalAppData + "Launcher")); // epicgameslauncher folder
					std::filesystem::remove_all((EpicGamesLocalAppData + "Launcher")); // epicgameslauncher folder
				}
				catch (...) {};

				try
				{
					std::filesystem::remove(EpicGamesAppData);
					std::filesystem::remove_all(EpicGamesAppData);
				}
				catch (...) {};

				try
				{
					std::filesystem::remove((EpicGamesAppData + "Launcher")); // epicgameslauncher folder
					std::filesystem::remove_all((EpicGamesAppData + "Launcher")); // epicgameslauncher folder
				}
				catch (...) {};

			}
			catch (...) {};

			try
			{
				for (int i = 0; i < 32; i++)
				{
					// volume shit - this scares m
					std::wstring VolumeShitData = (_(L"\\\\.\\PhysicalDrive").decrypt() + std::to_wstring(i));

					HANDLE device = CreateFileW(VolumeShitData.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
					if (device != INVALID_HANDLE_VALUE)
					{
						BYTE sector[512] = { 0 };
						DWORD read = 0;
						if (ReadFile(device, sector, sizeof(sector), &read, 0) && read == sizeof(sector))
						{
							for (DWORD i = 0; i < LENGTH(SECTORS); ++i)
							{
								PSECTOR s = &SECTORS[i];
								if (0 == memcmp(sector + s->NameOffset, s->Name, strlen(s->Name)))
								{
									*(PDWORD)(sector + s->SerialOffset) = (rand() << 16) + rand();
									if (INVALID_SET_FILE_POINTER != SetFilePointer(device, 0, 0, FILE_BEGIN))
									{
										WriteFile(device, sector, sizeof(sector), 0, 0);
									}

									break;
								}
							}
						}

						//CloseHandle(device);
					}
				}
			}
			catch (...)
			{

			}

			
			TryDeleteItemOnAllDrives(_(L"Windows\\System32\\restore\\MachineGuid.txt").decrypt(), false);
			TryDeleteItemOnAllDrives(_(L"Windows\\INF\\setupapi.dev.log").decrypt(), false);
			TryDeleteItemOnAllDrives(_(L"Windows\\INF\\setupapi.setup.log").decrypt(), false);
			TryDeleteItemOnAllDrives(_(L"Windows\\System32\\restore\\MachineGuid.txt").decrypt(), false);
			TryDeleteItemOnAllDrives(_(L"Users\\Public\\Libraries\\collection.dat").decrypt(), false);

			TryDeleteItemOnAllDrives(_(L"ProgramData\\NVIDIA").decrypt());
			TryDeleteItemOnAllDrives(_(L"NVIDIA Corporation\\ShadowPlay").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\Microsoft\\Feeds Cache").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\Microsoft\\Windows\\History").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\Microsoft\\Windows\\INetCache").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\LocalLow\\Microsoft\\CryptnetUrlCache\\MetaData").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\CrashDumps").decrypt());	
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\Microsoft\\Windows\\UsrClass.dat.LOCK").decrypt(), true);
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Roaming\\EasyAntiCheat").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\NVIDIA Corporation\\GfeSDK").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\NVIDIA\\GLCache").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\UnrealEngine").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\FortniteGame").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\EpicGamesLauncher").decrypt());
			TryDeleteItemOnAllDrivesCurrentUser(_(L"\\AppData\\Local\\Epic Games").decrypt());


			return true;
		}
	}
}