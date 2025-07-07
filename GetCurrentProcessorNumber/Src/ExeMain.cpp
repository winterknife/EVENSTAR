// ========================================================================
// File: ExeMain.cpp
//
// Author: winterknife
//
// Description: Source file that contains the EXE entry point
//
// Modifications:
//  2025-07-01	Created
//  2025-07-06  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/Common.h"
#include "../Inc/GetCurrentProcessorNumber.h"
#include <process.h>

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

#pragma CODE_BEGIN
/// @brief EXE entry point
/// @param None
/// @return None
extern "C" __declspec(noreturn) VOID __stdcall ExeEntry(
	VOID
) {
	DEBUG_PRINT("[*] %s Built %s %s\n", __MODULE__, __DATE__, __TIME__);

	system("PAUSE");

	if (*(BYTE*)(0x7FFE0000ULL + 0x02D4))
		__debugbreak();

	__nop();
	__nop();
	__nop();

	// Init local variables
	DWORD dwActiveProcessorCount = 0;
	DWORD dwIndex = 0;
	DWORD_PTR dwptrProcessorAffinityMask = 0;

	// Get the number of active logical processors in the system
	dwActiveProcessorCount = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
	DEBUG_PRINT("[+] Logical processor count = 0n%I32u\n", dwActiveProcessorCount);

	// Loop through all processors
	for (dwIndex = 0; dwIndex < dwActiveProcessorCount; dwIndex++) {
		// Set a processor affinity mask (CPU pinning) for all the threads of the current process
		dwptrProcessorAffinityMask = __ll_lshift(0x1, dwIndex);
		if (!SetProcessAffinityMask(GetCurrentProcess(), dwptrProcessorAffinityMask)) {
			DEBUG_PRINT("[-] SetProcessAffinityMask failed: 0n%I32u\n", GetLastError());
			goto cleanup;
		}
		DEBUG_PRINT("[+] Pinned all the threads of the current process to logical processor = 0n%I32u\n", dwIndex);

		// Get current processor number
		DEBUG_PRINT("[+] Current logical processor's ID = 0n%I32u\n", get_current_processor_number());
	}

	// Cleanup
cleanup:
	system("PAUSE");

	ExitProcess(0);
}
#pragma CODE_END

#pragma endregion