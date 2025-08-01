#pragma once

namespace Cleaner
{
	namespace WindowsInstall
	{
		bool DesktopNameCleaning()
		{
			Logging::PrintLog("cleaning windows desktop data & networking!\r\n");

			ULONGLONG Time_UpdateTimestamp = Utils::GetRandomUpdateTime();
			std::wstring DesktopName = Utils::GetRandomDesktopNameW();
			std::wstring UUID_WMSDK = Utils::GetUUIDW();
			DWORD RandomVolumeID = (ULONGLONG)(DWORD)(Utils::RandNum(20000, 30000));
			RandomVolumeID = RandomVolumeID * 100000;
			RandomVolumeID = abs((int)RandomVolumeID); // ensure positive.

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\ControlSet001\\Services\\Tcpip\\Parameters").decrypt(), _(L"NV Hostname").decrypt(), DesktopName))
			{
				Logging::PrintError(_("cleaner failed to set NV Hostname!").decrypt());
				return false;
			}

			Logging::PrintLog("set \"NV Hostname\" to \"%ls\"!", DesktopName.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\ControlSet001\\Services\\Tcpip\\Parameters").decrypt(), _(L"Hostname").decrypt(), DesktopName))
			{
				Logging::PrintError(_("cleaner failed to set Hostname!").decrypt());
				return false;
			}

			Logging::PrintLog(_("set \"Hostname\" to \"%ls\"!").decrypt(), DesktopName.c_str());

			Logging::PrintLog(_("set \"NV Hostname\" to \"%ls\"!").decrypt(), DesktopName.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ActiveComputerName").decrypt(), _(L"ComputerName").decrypt(), DesktopName))
			{
				Logging::PrintError("cleaner failed to set ActiveComputerName!");
				return false;
			}

			Logging::PrintLog(_("set \"ActiveComputerName\" to \"%ls\"!").decrypt(), DesktopName.c_str());

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName").decrypt(), _(L"ComputerName").decrypt(), DesktopName))
			{
				Logging::PrintError("cleaner failed to set ComputerName!");
				return false;
			}

			Logging::PrintLog("set \"ComputerName\" to \"%ls\"!", DesktopName.c_str());

			if (!Registry::SetString(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\Windows Media\\WMSDK\\General").decrypt(), _(L"ComputerName").decrypt(), DesktopName))
			{
				Logging::PrintError("cleaner failed to set WMSDK_ComputerName!");
				return false;
			}

			Logging::PrintLog("set \"WMSDK_ComputerName\" to \"%ls\"!", DesktopName.c_str());

			if (!Registry::SetString(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\Windows Media\\WMSDK\\General").decrypt(), _(L"UniqueID").decrypt(), UUID_WMSDK))
			{
				Logging::PrintError("cleaner failed to set WMSDK_UniqueID!");
				return false;
			}


			Logging::PrintLog("set \"WMSDK_UniqueID\" to \"%ls\"!", UUID_WMSDK.c_str());

			if (!Registry::SetDWORD(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\Windows Media\\WMSDK\\General").decrypt(), _(L"VolumeSerialNumber").decrypt(), RandomVolumeID))
			{
				Logging::PrintError("cleaner failed to set WMSDK_VolumeSerialNumber!");
				return false;
			}

			Logging::PrintLog("set \"WMSDK_VolumeSerialNumber\" to \"%d\"!", RandomVolumeID);

			if (Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SYSTEM\\ControlSet001\\Services\\EventLog\\State").decrypt(), _(L"LastComputerName").decrypt(), DesktopName))
				Logging::PrintLog("set \"EvtLog_LastComputerName\" to \"%ls\"!", DesktopName.c_str());

			return true;
		}

		bool CleanWindowsInstallData()
		{
			Logging::PrintLog("cleaning windows install!\r\n");

			DWORD InstallDate = Utils::GetRandomInstallDate();
			ULONGLONG InstallTime = Utils::GetRandomInstallTime();

			if (!Registry::SetDWORD(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion").decrypt(), _(L"InstallDate").decrypt(), InstallDate))
			{
				Logging::PrintError("cleaner failed to set install date!");
				return false;
			}

			if (!Registry::SetDWORD(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows NT\\CurrentVersion").decrypt(), _(L"InstallDate").decrypt(), 0))
			{
				Logging::PrintError("cleaner failed to set wow6432node install date!");
				return false;
			}

			Logging::PrintLog("set install date to \"%d\"!", InstallTime);

			if (!Registry::SetQWORD(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion").decrypt(), _(L"InstallTime").decrypt(), InstallTime))
			{
				Logging::PrintError("cleaner failed to set install time!");
				return false;
			}

			Logging::PrintLog("set install time to \"%llu\"!", InstallTime);

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion").decrypt(), _(L"RegisteredOrganization").decrypt(), L""))
			{
				Logging::PrintError("cleaner failed to set RegisteredOrganization!");
				return false;
			}

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows NT\\CurrentVersion").decrypt(), _(L"RegisteredOrganization").decrypt(), L""))
			{
				Logging::PrintError("cleaner failed to set wow6432node_RegisteredOrganization!");
				return false;
			}
				
			Logging::PrintLog("set RegisteredOrganization to \"\"!"); // we shouldn't change

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion").decrypt(), _(L"RegisteredOwner").decrypt(), _(L"Windows User").decrypt()))
			{
				Logging::PrintError("cleaner failed to set RegisteredOwner!");
				return false;
			}

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows NT\\CurrentVersion", L"RegisteredOwner", _(L"Windows User").decrypt()))
			{
				Logging::PrintError("cleaner failed to set wow6432node_RegisteredOwner!");
				return false;
			}

			Logging::PrintLog("set RegisteredOwner to \"Windows User\"!"); // we shouldn't change

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion").decrypt(), _(L"ProductId").decrypt(), _(L"00000-00000-00000-00000").decrypt())) // generic
			{
				Logging::PrintError("cleaner failed to set ProductId!");
				return false;
			}

			Logging::PrintLog("set ProductId to generic \"00331-10000-00001-AA228\"!"); // we shouldn't change

			std::wstring GUIDForTracing = Utils::GetUUIDW(false);

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Tracing\\Microsoft\\Profile\\Profile").decrypt(), _(L"Guid").decrypt(), GUIDForTracing))
			{
				Logging::PrintError("cleaner failed to set TracingGuid!");
				return false;
			}

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows NT\\CurrentVersion\\Tracing\\Microsoft\\Profile\\Profile").decrypt(), L"Guid", GUIDForTracing))
			{
				Logging::PrintError("cleaner failed to set wow6432node_TracingGuid!");
				return false;
			}

			Logging::PrintLog("set TracingGUID to \"%ls\"!", GUIDForTracing.c_str());

			std::wstring GUIDForFirewall = Utils::GetUUIDW(false);

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Tracing\\Microsoft\\FirewallAPI\\FirewallAPI").decrypt(), _(L"Guid").decrypt(), GUIDForFirewall))
			{
				Logging::PrintError("cleaner failed to set FirewallGUID!");
				return false;
			}

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows NT\\CurrentVersion\\Tracing\\Microsoft\\FirewallAPI\\FirewallAPI").decrypt(), L"Guid", GUIDForFirewall))
			{
				Logging::PrintError("cleaner failed to set wow6432node_FirewallGUID!");
				return false;
			}

			Logging::PrintLog("set FirewallGUID to \"%ls\"!", GUIDForFirewall.c_str());

			std::wstring GUIDForNCDTrace = Utils::GetUUIDW(false);

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Tracing\\Microsoft\\NCDTrace\\UmBusDriver\\CtlGuid").decrypt(), L"Guid", GUIDForNCDTrace))
			{
				Logging::PrintError("cleaner failed to set NCDTraceGUID!");
				return false;
			}

			Logging::PrintLog("set NCDTraceGUID to \"%ls\"!", GUIDForNCDTrace.c_str());

			std::wstring GUIDForPlugAndPlayTrace = Utils::GetUUIDW(false);

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Tracing\\Microsoft\\PlugPlay\\SETUPAPI\\PlugPlay").decrypt(), L"Guid", GUIDForPlugAndPlayTrace))
			{
				Logging::PrintError("cleaner failed to set PlugAndPlayGUID!");
				return false;
			}

			Logging::PrintLog("set PlugAndPlayGUID to \"%ls\"!", GUIDForPlugAndPlayTrace.c_str());

			std::wstring UpdateAgent_DeviceID = Utils::GetUUIDW(false);

			if (!Registry::SetString(HKEY_LOCAL_MACHINE, _(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OneSettings\\WSD\\UpdateAgent\\QueryParameters").decrypt(), L"deviceId", UpdateAgent_DeviceID))
			{
				Logging::PrintError("cleaner failed to set UpdateAgent_DeviceID!");
				return false;
			}

			Logging::PrintLog("set UpdateAgent_DeviceID to \"%ls\"!", UpdateAgent_DeviceID.c_str());

			std::wstring LID_Guid = Utils::RandomStringHexWLIDGen(16, true, true);

			if (!Registry::SetString(HKEY_CURRENT_USER, _(L"SOFTWARE\\Microsoft\\IdentityCRL\\ExtendedProperties").decrypt(), L"LID", LID_Guid))
			{
				Logging::PrintError("cleaner failed to set LID_Guid!");
				return false;
			}

			Logging::PrintLog("set LID_Guid to \"%ls\"!", LID_Guid.c_str());

			Registry::SpoofUnique(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate", L"AccountDomainSid");
			Registry::SpoofUnique(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate", L"PingID");
			Registry::SpoofQWORD(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\SQMClient", L"WinSqmFirstSessionStartTime");
				Registry::DeleteValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Direct3D", L"WHQLClass");

			Registry::SpoofUnique(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\IdentityCRL\\ExtendedProperties", L"LID");
			Registry::SpoofBinary(HKEY_LOCAL_MACHINE, L"SYSTEM\\ControlSet001\\Services\\Tcpip\\Parameters", L"Dhcpv6DUID");

			return DesktopNameCleaning();
		}
	}
}