#include "pch.h"
#include "Utils/Utils.h"
#include "winternl.h"
#include "Psapi.h"
#include "KernelBase.h"

namespace winrt::StarlightGUI::implementation {
	DWORD64 KernelBase::GetCIBaseAddress() {
		LPVOID drivers[1024];
		DWORD cbNeeded;

		if (!K32EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded)) {
			return 0;
		}

		int driverCount = cbNeeded / sizeof(drivers[0]);

		for (int i = 0; i < driverCount; i++) {
			WCHAR driverName[MAX_PATH];
			if (K32GetDeviceDriverBaseNameW(drivers[i], driverName, sizeof(driverName))) {

				if (_wcsicmp(driverName, L"ci.dll") == 0) {
					return (DWORD64)drivers[i];
				}
			}
		}

		return 0;
	}
}