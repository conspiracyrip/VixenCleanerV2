#pragma once

namespace Utils
{
	DWORD CachedInstallDate = 0;
	ULONGLONG CachedInstallTime = 0;
	std::wstring CachedRandomDesktopNameW = L"";
	std::string CachedRandomDesktopNameA = "";

	int RandNum(int Min, int Max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(Min, Max);
		return distr(gen);
	}

	ULONGLONG EpochToFileTime(ULONGLONG epochSeconds)
	{
		const ULONGLONG WINDOWS_TO_UNIX_EPOCH = 11644473600ULL;
		return (epochSeconds + WINDOWS_TO_UNIX_EPOCH) * 10000000ULL;
	}

	bool InitValuesForInstallTime(bool Override = false)
	{
		static bool bInitYet = false;
		if (bInitYet && Override)
			bInitYet = true;

		if (!bInitYet)
		{
			int InstallRandomEpoch = RandNum(1500000000, 1699999999); // around 2017 to around 2023
			CachedInstallDate = static_cast<DWORD>(InstallRandomEpoch);
			CachedInstallTime = EpochToFileTime(static_cast<ULONGLONG>(InstallRandomEpoch));
			bInitYet = true;
		}

		return bInitYet;
	}

	ULONGLONG GetRandomUpdateTime()
	{
		int InstallRandomEpoch = RandNum(1500000000, 1699999999); // around 2017 to around 2023
		return EpochToFileTime(static_cast<ULONGLONG>(InstallRandomEpoch));
	}

	DWORD GetRandomInstallDate(bool Override = false)
	{
		if (!Override) return CachedInstallDate;
		

		DWORD OldInstallDate = CachedInstallDate;  // cache ts
		ULONGLONG OldInstallTime = CachedInstallTime; // cache ts
		InitValuesForInstallTime(Override);

		ULONGLONG ReturnValue = CachedInstallTime;

		CachedInstallDate = OldInstallDate;
		CachedInstallTime = OldInstallTime;

		return CachedInstallDate;
	}

	//ULONGLONG GetRandomInstallTime()
	//{
	//	return CachedInstallTime;
	//}

	ULONGLONG GetRandomInstallTime(bool Override = false)
	{
		if (!Override) return CachedInstallTime;

		DWORD OldInstallDate = CachedInstallDate;  // cache ts
		ULONGLONG OldInstallTime = CachedInstallTime; // cache ts
		InitValuesForInstallTime(Override);

		ULONGLONG ReturnValue = CachedInstallTime;

		CachedInstallDate = OldInstallDate;
		CachedInstallTime = OldInstallTime;

		return ReturnValue;
	}

	std::wstring GetUUIDW(bool Brackets = true)
	{
		auto res = uuid_v4::UUID::New();

		return res.WString(Brackets);
	}

	std::wstring GetUUIDNoDashesW(bool Brackets = true)
	{
		auto res = uuid_v4::UUID::New();

		std::wstring resStr = res.WString(Brackets);;

		resStr.erase(std::remove(resStr.begin(), resStr.end(), '-'), resStr.end());

		return resStr;
	}

	std::string GetUUIDNoDashesA(bool Brackets = true)
	{
		auto res = uuid_v4::UUID::New();

		std::string resStr = res.String(Brackets);;

		resStr.erase(std::remove(resStr.begin(), resStr.end(), '-'), resStr.end());

		return resStr;
	}

	std::string GetUUID(bool Brackets = true)
	{
		auto res = uuid_v4::UUID::New();

		return res.String(Brackets);
	}

	std::string RandomStringA(int Length = 8, bool CapsOnly = false, bool IncludeNumbers = true)
	{
		const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::string lower = "abcdefghijklmnopqrstuvwxyz";
		const std::string digits = "0123456789";

		std::string charset = upper;
		if (!CapsOnly)
			charset += lower;
		if (IncludeNumbers)
			charset += digits;

		std::string result;
		result.reserve(Length);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, static_cast<int>(charset.size()) - 1);

		for (int i = 0; i < Length; ++i)
			result += charset[dist(gen)];

		return result;
	}

	std::string RandomStringHexA(int Length = 8, bool CapsOnly = false, bool IncludeNumbers = true)
	{
		const std::string upper = "ABCDEF";
		const std::string lower = "abcdef";
		const std::string digits = "0123456789";

		std::string charset = upper;
		if (!CapsOnly)
			charset += lower;
		if (IncludeNumbers)
			charset += digits;

		std::string result;
		result.reserve(Length);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, static_cast<int>(charset.size()) - 1);

		for (int i = 0; i < Length; ++i)
			result += charset[dist(gen)];

		return result;
	}

	std::wstring RandomStringHexW(int Length = 8, bool CapsOnly = false, bool IncludeNumbers = true)
	{
		const std::wstring upper = L"ABCDEF";
		const std::wstring lower = L"abcdef";
		const std::wstring digits = L"0123456789";

		std::wstring charset = upper;
		if (!CapsOnly)
			charset += lower;
		if (IncludeNumbers)
			charset += digits;

		std::wstring result;
		result.reserve(Length);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, static_cast<int>(charset.size()) - 1);

		for (int i = 0; i < Length; ++i)
			result += charset[dist(gen)];

		return result;
	}


	std::wstring RandomStringHexWLIDGen(int Length = 8, bool CapsOnly = false, bool IncludeNumbers = true)
	{
		const std::wstring upper = L"ABCDEF";
		const std::wstring lower = L"abcdef";
		const std::wstring digits = L"012345";

		std::wstring charset = upper;
		if (!CapsOnly)
			charset += lower;
		if (IncludeNumbers)
			charset += digits;

		std::wstring result;
		result.reserve(Length);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, static_cast<int>(charset.size()) - 1);

		for (int i = 0; i < Length; ++i)
			result += charset[dist(gen)];

		return result;
	}

	std::wstring RandomStringW(int Length = 8, bool CapsOnly = false, bool IncludeNumbers = true)
	{
		const std::wstring upper = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::wstring lower = L"abcdefghijklmnopqrstuvwxyz";
		const std::wstring digits = L"0123456789";

		std::wstring charset = upper;
		if (!CapsOnly)
			charset += lower;
		if (IncludeNumbers)
			charset += digits;

		std::wstring result;
		result.reserve(Length);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, static_cast<int>(charset.size()) - 1);

		for (int i = 0; i < Length; ++i)
			result += charset[dist(gen)];

		return result;
	}

	bool SetupRandomAndConstants()
	{
		bool InstallTime = InitValuesForInstallTime();

		if (!InstallTime) return false;

		std::string RandomDesktopNameA = Utils::RandomStringA(7, true, false);
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring RandomDesktopNameW = converter.from_bytes(RandomDesktopNameA);

		CachedRandomDesktopNameW = L"DESKTOP-" + RandomDesktopNameW;
		CachedRandomDesktopNameA = "DESKTOP-" + RandomDesktopNameA;

		return true;
	}

	std::string GetRandomDesktopNameA()
	{
		return CachedRandomDesktopNameA;
	}

	std::wstring GetRandomDesktopNameW()
	{
		return CachedRandomDesktopNameW;
	}
}

namespace Processes
{

	uintptr_t GetProcessIDByName(std::wstring ProcessName)
	{
		HANDLE snapshot_handle;
		if ((snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
			return 0;

		DWORD pid = 0;
		PROCESSENTRY32W pe;
		memset(&pe, 0, sizeof(PROCESSENTRY32W));
		pe.dwSize = sizeof(PROCESSENTRY32W);
		if (Process32FirstW(snapshot_handle, &pe))
		{
			while (Process32NextW(snapshot_handle, &pe))
			{
				if (pe.szExeFile == ProcessName)
				{
					pid = pe.th32ProcessID;
					break;
				}
			}
		}
		else
		{
			if (snapshot_handle)
			{
				try { CloseHandle(snapshot_handle); }
				catch (...) {}
			}
		}


		if (snapshot_handle)
		{
			try { CloseHandle(snapshot_handle); }
			catch (...) {}
		}


		return pid;
	}

	HANDLE GetProcessHandleByName(std::wstring ProcessName)
	{
		uintptr_t PID = GetProcessIDByName(ProcessName);
		if (!PID) return INVALID_HANDLE_VALUE;

		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, PID);
		if (hProcess && hProcess != INVALID_HANDLE_VALUE)
			return hProcess;

		return INVALID_HANDLE_VALUE;
	}

	bool KillProcessByName(std::wstring ProcessName, NTSTATUS ExitStatus = STATUS_ACCESS_VIOLATION)
	{
		HANDLE ProcessHandle = GetProcessHandleByName(ProcessName);
		if (ProcessHandle && ProcessHandle != INVALID_HANDLE_VALUE)
		{
			if (NtTerminateProcess(ProcessHandle, ExitStatus) == ERROR_SUCCESS)
				return true;
		}

		return false;
	}
}