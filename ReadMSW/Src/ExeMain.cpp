// ========================================================================
// File: ExeMain.cpp
//
// Author: winterknife
//
// Description: Source file that contains the EXE entry point
//
// Modifications:
//  2025-01-08	Created
//  2025-01-09  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/Common.h"
#include "../Inc/ReadMsw.h"
#define _NO_CRT_STDIO_INLINE
#include <stdio.h>
#include <process.h>

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

#pragma CODE_BEGIN
/// @brief EXE entry point
/// @param None
/// @return None
extern "C" __declspec(noreturn) VOID __stdcall ExeInit(
	VOID
) {
	printf("[*] %s Built %s %s\n", __MODULE__, __DATE__, __TIME__);

	if (IsDebuggerPresent())
		__debugbreak();
	else
		system("PAUSE");

	__nop();
	__nop();
	__nop();

	// Init local variables
	BOOLEAN bProtectionEnable = FALSE;

	// Check if Segmentation is enabled
	bProtectionEnable = is_protected_mode_enabled();
	if (bProtectionEnable)
		printf("Processor Execution Mode == Protected Mode\n");
	else
		printf("Processor Execution Mode == Real-Address Mode\n");

	__nop();
	__nop();
	__nop();

	if (IsDebuggerPresent())
		__debugbreak();
	else
		system("PAUSE");

	ExitProcess(0);
}
#pragma CODE_END

#pragma endregion