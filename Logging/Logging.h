#pragma once


namespace Logging
{
	void PrintError(std::string ErrorText, bool bWait = true, DWORD WaitTime = 5000)
	{

#if !DISABLE_ALL_LOGGING
#if SHOW_DEBUG_LOGGING
		printf("[ERROR] %s!\r\n", ErrorText.c_str());
#endif
#endif

		//if (bWait)
			//Sleep(WaitTime);
	}

	void PrintFatalError(std::string ErrorText, DWORD WaitTime = 10000)
	{

#if !DISABLE_ALL_LOGGING
		printf(_("[FATAL ERROR] %s!\r\n").decrypt(), ErrorText.c_str());
#endif

		//Sleep(WaitTime);
	}

	void PrintLog(const char* format, ...)
	{
		char buffer[1024];

		va_list args;
		va_start(args, format);
		vsnprintf(buffer, sizeof(buffer), format, args);
		va_end(args);

#if !DISABLE_ALL_LOGGING
#if SHOW_DEBUG_LOGGING
		printf("[inf] %s\r\n", buffer);
#endif
#endif

		// cus htis is insanely fast for a cleaner, make it seem like its doing more..
#if !SHOW_DEBUG_LOGGING
		//int RandNum = Utils::RandNum(29, 59);
		//Sleep(RandNum);
#endif

	}
}