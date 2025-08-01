#pragma once

namespace Cleaner
{
	namespace HWID
	{

		bool FixupSerials()	
		{
			Cleaner::HWID::FixupHWIDSerials();
			return true;
		}


		bool CleanHWIDTraces()
		{
			std::wstring UUID_OneDrive = Utils::GetUUIDW(false);
			std::wstring UMID_OneDrive = Utils::GetUUIDW(false);
			std::wstring UUID_MachineGuid = Utils::GetUUIDW(false);
			std::wstring LastBiosKey_GUID = Utils::GetUUIDW(false);
			std::wstring BackupProductKeyDefault_GUID = Utils::GetUUIDW(false);
			std::wstring deviceId_GUID = Utils::GetUUIDW(false);

			std::wstring UUID_ComputerHardwareId = Utils::GetUUIDW(true);
			std::wstring UUID_ComputerHardwareIds = Utils::GetUUIDW(true);
			std::wstring WppRecorder_Trace_Guid = Utils::GetUUIDW(true);
			std::wstring UUID_Config_HwProfileGuid = Utils::GetUUIDW(true);

			std::wstring UUID_SusClientId = Utils::GetUUIDW(true);

			if (!Registry::SetString(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\OneDrive\\QoS").decrypt(), _(L"UUID").decrypt(), UUID_OneDrive))
			{
				Logging::PrintError("cleaner failed to set OneDrive_UUID!");
				return false;
			}


			Logging::PrintLog("set \"OneDrive_UUID\" to \"%ls\"!", UUID_OneDrive.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Services\\kbdhid\\Parameters").decrypt(), _(L"WppRecorder_TraceGuid").decrypt(), WppRecorder_Trace_Guid))
			{
				Logging::PrintError("cleaner failed to set WppRecorder_TraceGuid!");
				return false;
			}

			Logging::PrintLog("set \"WppRecorder_TraceGuid\" to \"%ls\"!", WppRecorder_Trace_Guid.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Services\\kbdclass\\Parameters").decrypt(), _(L"WppRecorder_TraceGuid").decrypt(), WppRecorder_Trace_Guid))
			{
				Logging::PrintError("cleaner failed to set WppRecorder_TraceGuid!");
				return false;
			}

			Logging::PrintLog("set \"WppRecorder_TraceGuid\" to \"%ls\"!", WppRecorder_Trace_Guid.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Services\\mouhid\\Parameters").decrypt(), _(L"WppRecorder_TraceGuid").decrypt(), WppRecorder_Trace_Guid))
			{
				Logging::PrintError("cleaner failed to set WppRecorder_TraceGuid!");
				return false;
			}

			Logging::PrintLog("set \"WppRecorder_TraceGuid\" to \"%ls\"!", WppRecorder_Trace_Guid.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows\\Win32kWPP\\Parameters").decrypt(), _(L"WppRecorder_TraceGuid").decrypt(), WppRecorder_Trace_Guid))
			{
				Logging::PrintError("cleaner failed to set WppRecorder_TraceGuid!");
				return false;
			}

			Logging::PrintLog("set \"WppRecorder_TraceGuid\" to \"%ls\"!", WppRecorder_Trace_Guid.c_str());


			Logging::PrintLog("set \"OneDrive_UUID\" to \"%ls\"!", UUID_OneDrive.c_str());

			if (!Registry::SetString(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\OneDrive\\QoS").decrypt(), _(L"UMID").decrypt(), UMID_OneDrive))
			{
				Logging::PrintError("cleaner failed to set OneDrive_UMID!");
				return false;
			}

			Logging::PrintLog("set \"OneDrive_UMID\" to \"%ls\"!", UMID_OneDrive.c_str());

			Logging::PrintLog("set \"OneDrive_UUID\" to \"%ls\"!", UUID_OneDrive.c_str());

			if (!Registry::SetString(HKEY_CURRENT_USER, _(L"SYSTEM\\CurrentControlSet\\Services\\ClipSVC\\Parameters").decrypt(), _(L"LastBiosKey").decrypt(), LastBiosKey_GUID))
			{
				Logging::PrintError("cleaner failed to set LastBiosKey_GUID!");
				return false;
			}

			Logging::PrintLog("set \"LastBiosKey\" to \"%ls\"!", LastBiosKey_GUID.c_str());


			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\SoftwareProtectionPlatform").decrypt(), _(L"LastProductKeyPid").decrypt(), L" "))
			{
				Logging::PrintError("cleaner failed to set LastProductKeyPid!");
				return false;
			}

			Logging::PrintLog("set \"LastProductKeyPid\" to \"%ls\"!", " ");

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Cryptography").decrypt(), _(L"MachineGuid").decrypt(), UUID_MachineGuid))
			{
				Logging::PrintError("cleaner failed to set Cryptography_MachineGuid!");
				return false;
			}

			Logging::PrintLog("set \"Cryptography_MachineGuid\" to \"%ls\"!", UUID_MachineGuid.c_str());


			if (!Registry::SetString(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\DeveloperTools").decrypt(), _(L"deviceId").decrypt(), deviceId_GUID))
			{
				Logging::PrintError("cleaner failed to set deviceId!");
				return false;
			}

			Logging::PrintLog("set \"deviceId\" to \"%ls\"!", deviceId_GUID.c_str());

			Logging::PrintLog("set \"LastBiosKey\" to \"%ls\"!", LastBiosKey_GUID.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\SoftwareProtectionPlatform").decrypt(), _(L"BackupProductKeyDefault").decrypt(), BackupProductKeyDefault_GUID))
			{
				Logging::PrintError("cleaner failed to set BackupProductKeyDefault!");
				return false;
			}

			Logging::PrintLog("set \"BackupProductKeyDefault\" to \"%ls\"!", BackupProductKeyDefault_GUID.c_str());


			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\SystemInformation").decrypt(), _(L"ComputerHardwareId").decrypt(), UUID_ComputerHardwareId))
			{
				Logging::PrintError("cleaner failed to set SystemInformation_ComputerHardwareId!");
				return false;
			}

			Logging::PrintLog("set \"SystemInformation_ComputerHardwareId\" to \"%ls\"!", UUID_ComputerHardwareId.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\SystemInformation").decrypt(), _(L"ComputerHardwareIds").decrypt(), UUID_ComputerHardwareIds))
			{
				Logging::PrintError("cleaner failed to set SystemInformation_ComputerHardwareIds!");
				return false;
			}

			Logging::PrintLog("set \"SystemInformation_ComputerHardwareIds\" to \"%ls\"!", UUID_ComputerHardwareIds.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0001").decrypt(), _(L"HwProfileGuid").decrypt(), UUID_Config_HwProfileGuid))
			{
				Logging::PrintError("cleaner failed to set Config_HwProfileGuid!");
				return false;
			}

			Logging::PrintLog("set \"Config_HwProfileGuid\" to \"%ls\"!", UUID_Config_HwProfileGuid.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate").decrypt(), _(L"SusClientId").decrypt(), UUID_SusClientId))
			{
				Logging::PrintError("cleaner failed to set Updater_SusClientId!");
				return false;
			}

			Logging::PrintLog("set \"Updater_SusClientId\" to \"%ls\"!", UUID_SusClientId.c_str());

			//DWORD InstallDateNetwork = Utils::GetRandomInstallDate();
			ULONGLONG InstallTimeNetwork = Utils::GetRandomInstallTime(true); // override for new :>


			// slight overkill but oh well!
			try
			{
				std::wstring BasePath = _(L"SYSTEM\\ControlSet001\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}\\000").decrypt();

				for (int i = 0; i < 69; i++)
				{
					std::wstring TargetPath = BasePath + std::to_wstring(i); // 1-70

					HKEY Key;
					if (RegOpenKeyW(HKEY_LOCAL_MACHINE, TargetPath.c_str(), &Key) == 0)
					{
						bool bIsFake = false;
						
						// RegQueryValueExW(hParams, L"EDID", NULL, &type, NULL, &dataSize)
					
						DWORD type = 0, dataSize = 0;
						if ( 
							RegQueryValueExW(Key, L"InfPath", NULL, &type, NULL, &dataSize) != 0 && // if a driver is missing all these honestly just kill the driver anyways
							RegQueryValueExW(Key, L"Characteristics", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"ProviderName", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"DriverDesc", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"MatchingDeviceId", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"IfType", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"*NdisDeviceType", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"IfType", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"*IfType", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"ComponentId", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"NetLuidIndex", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"EnableForRouting", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"InfSection", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"DriverDateData", NULL, &type, NULL, &dataSize) != 0 &&
							RegQueryValueExW(Key, L"DriverVersion", NULL, &type, NULL, &dataSize) != 0)
						{
							RegCloseKey(Key);

							bIsFake = true;

							Registry::DeleteValue(HKEY_LOCAL_MACHINE, TargetPath, _(L"NetworkAddress").decrypt());
							Registry::SetQWORD(HKEY_LOCAL_MACHINE, TargetPath, _(L"NetworkInterfaceInstallTimestamp").decrypt(), InstallTimeNetwork);
						}

						if (bIsFake) // accidentally forgot to check keys, cleanup mess if we've caused one.. >_<
						{
							RegCloseKey(Key);

							RegDeleteKeyW(HKEY_LOCAL_MACHINE, TargetPath.c_str());
						}
					}

				}
			}
			catch (...) {};


			Registry::SpoofBinary(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\TPM\\WMI", L"WindowsAIKHash");
			Registry::SpoofBinary(HKEY_CURRENT_USER, L"Software\\Classes\\Installer\\Dependencies", L"MSICache");

			Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Diagnostics\\DiagTrack\\SettingsRequests").decrypt());
			Registry::SpoofQWORD(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Diagnostics\\DiagTrack\\SevilleEventlogManager").decrypt(), _(L"LastEventlogWrittenTime").decrypt());
			Registry::SpoofQWORD(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\SoftwareProtectionPlatform\\Activation").decrypt(), _(L"ProductActivationTime").decrypt());
			Registry::DeleteValue(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\SoftwareProtectionPlatform").decrypt(), _(L"BackupProductKeyDefault").decrypt());
			Registry::DeleteValue(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\SoftwareProtectionPlatform").decrypt(), _(L"actionlist").decrypt());
			Registry::DeleteValue(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\SoftwareProtectionPlatform").decrypt(), _(L"ServiceSessionId").decrypt());
			Registry::DeleteKey(HKEY_CURRENT_USER, _(L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist").decrypt());

			Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\MountedDevices").decrypt());
			Registry::DeleteKey(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Dfrg\\Statistics").decrypt());
			Registry::DeleteKey(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\BitBucket\\Volume").decrypt());
			Registry::DeleteKey(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\\CPC\\Volume").decrypt());
			Registry::DeleteKey(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2").decrypt());
			Registry::DeleteValue(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\BitBucket").decrypt(), _(L"LastEnum").decrypt());
	
			return true;
		}
	}
}