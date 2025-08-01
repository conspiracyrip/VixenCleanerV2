#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Psapi.h>
#include <TlHelp32.h>
#include <filesystem>
#define DO_NOT_INCLUDE_STR_CRYPTOR 1
#include "./Prot/LibProt.h"

#define SHOW_DEBUG_LOGGING 0
#define DISABLE_ALL_LOGGING 0

#include "./Includes/Defs.h"

#include "./Utils/Registry.h"
#include "./Utils/uuid.h"
#include "./Utils/Serials.h"

#include "./Utils/Utils.h"
#include "./Includes/xor.h"

#include "./Logging/Logging.h"

#include "./Cleaner/Install/WindowsInstall.h"
#include "./Cleaner/Other/Other.h"
#include "./Cleaner/Traces/HWID.h"

#include "./Cleaner/Init/CleanerInit.h"


// trace todo
// desktop name - HKEY_CURRENT_USER\Volatile Environment
// desktop name - HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Authentication\LogonUI\SessionData\1
// desktop name - HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Group Policy\DataStore\Machine\0
// desktop name - HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Group Policy\DataStore\S-1-5-21-716372044-2609782478-3689899436-1000\0
// desktop name - HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Group Policy\DataStore\Machine\0
// desktop name - HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Group Policy\DataStore\S-1-5-21-716372044-2609782478-3689899436-1000\0
// GUID/HWID - 
// GUID/HWID - 
// GUID/HWID - 
// GUID/HWID - 
// GUID/HWID - 



int main()
{
	
	uintptr_t AppBaseAddr = LibProt::GetMainAppBase();
	bool SetFakeEntryPointInsideModule = false;
	bool CleanExports = true;
	bool CleanTLSCallbacks = true;

	bool InitValue = LibProt::Initialize(AppBaseAddr, SetFakeEntryPointInsideModule, CleanExports, CleanTLSCallbacks);
	if (!InitValue) return 0; // failed init

	// PAGE_NOACCESS the pe, makes crash on access.
	if (!LibProt::PostInit::PostInitMakePENoAccess(AppBaseAddr))
	{
		//printf("LibProt::PostInit::PostInitMakePENoAccess(0x%p) failed!\r\n", AppBaseAddr);
		return false;
	}

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut != INVALID_HANDLE_VALUE)
	{
		DWORD dwMode = 0;
		if (GetConsoleMode(hOut, &dwMode))
		{
			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			if (SetConsoleMode(hOut, dwMode))
			{
				std::cout << _("\x1B[2J\x1B[H").decrypt();
			}
		}
	}

	SetConsoleTitleA(_("Vixen Cleaner - discord.gg/vixencommunity - t.me/vixenud"));

	printf(_("initializing cleaner...!\r\n\r\n\r\nmade by conspiracy for FREE in discord.gg/vixencommunity - t.me/vixenud..\r\nif you paid for this product, YOU GOT SCAMMED...\r\nTHIS PRODUCT ALWAYS HAS AND ALWAYS WILL BE FREE...\r\n").decrypt());


#if !SHOW_DEBUG_LOGGING
	//int RandTimePreInit = Utils::RandNum(2699, 5999);
	//Sleep(RandTimePreInit);
#endif

	if (!CleanerInit())
	{
		Logging::PrintFatalError(_("cleaner failed to initialize! exiting in 10 seconds...").decrypt());

		return 0;
	}

	printf(_("\r\n\r\ninitialized cleaner successfully...! it is recommended you use before and after spoofing..\r\n\r\n\r\nmade by conspiracy..\r\n\r\n").decrypt());
#if !SHOW_DEBUG_LOGGING
	//int RandTimePostInit = Utils::RandNum(4999, 7599);
	//Sleep(RandTimePostInit);
#endif

	/*
	DWORD InstallDate = Utils::GetRandomInstallDate();
	ULONGLONG InstallTime = Utils::GetRandomInstallTime();

	std::string UUID1 = Utils::GetUUID();
	std::string UUID2 = Utils::GetUUID();


	printf("Utils::GetRandomInstallDate(): %d!\r\n", InstallDate);
	printf("Utils::GetRandomInstallTime(): %llu!\r\n", InstallTime);

	printf("Utils::GetUUID(): %s! (first)\r\n", UUID1.c_str());
	printf("Utils::GetUUID(): %s! (second)\r\n", UUID2.c_str());
	*/
	printf(_("\r\n\r\ncleaning....! please be patient..\r\n").decrypt());
	
	auto t_1 = std::chrono::high_resolution_clock::now();

	if (!Cleaner::Clean())
	{
		Logging::PrintFatalError(_("cleaner failed to clean properly! exiting in 10 seconds...").decrypt());

		return 0;
	}

#if !SHOW_DEBUG_LOGGING
	//int RandTimePostCompletion = Utils::RandNum(1999, 2599);
	//Sleep(RandTimePostCompletion);
#endif

	auto t_C = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_seconds = t_C - t_1;


	printf(_("\r\nCLEANED SUCCESSFULLY! Restart your PC to finish the cleaning process.\r\nCleaning took: %.3f seconds..\r\n\r\n\r\n").decrypt(), elapsed_seconds.count());
	printf(_("made by conspiracy for FREE in discord.gg/vixencommunity - t.me/vixenud..\r\nif you paid for this product, YOU GOT SCAMMED...\r\nTHIS PRODUCT ALWAYS HAS AND ALWAYS WILL BE FREE...\r\n").decrypt());
	printf(_("ENJOY!\r\n").decrypt());

	Sleep(15000);

	return 1;
}