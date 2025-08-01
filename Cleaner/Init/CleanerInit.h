#pragma once

bool CleanerInit()
{
	if (!Utils::SetupRandomAndConstants())
	{
		Logging::PrintError("failed to setup constants!");

		return false;
	}

	Processes::KillProcessByName(_(L"FortniteClient-Win64-Shipping.exe").decrypt());
	Processes::KillProcessByName(_(L"FortniteClient-Win64-Shipping_EAC_EOS.exe").decrypt());
	Processes::KillProcessByName(_(L"EpicGamesLauncher.exe").decrypt());
	Processes::KillProcessByName(_(L"EpicWebHelper.exe").decrypt());

	return true;
}

namespace Cleaner
{
	bool Clean()
	{
		if (!Cleaner::WindowsInstall::CleanWindowsInstallData())
		{
			Logging::PrintError("Cleaner::WindowsInstall::CleanWindowsInstallData() failed, aborting...");

			return false;
		}

		if (!Cleaner::HWID::CleanHWIDTraces())
		{
			Logging::PrintError("Cleaner::HWID::CleanHWIDTraces() failed, aborting...");

			return false;
		}

		if (!Cleaner::Other::CleanOtherMisc())
		{
			Logging::PrintError("Cleaner::Other::CleanOtherMisc() failed, aborting...");

			return false;
		}

		if (!Cleaner::HWID::FixupSerials())
		{
			Logging::PrintError("Cleaner::Other::CleanOtherMisc() failed, aborting...");

			return false;
		}

		return true;
	}
}