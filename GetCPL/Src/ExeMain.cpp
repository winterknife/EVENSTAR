// ========================================================================
// File: ExeMain.cpp
//
// Author: winterknife
//
// Description: Source file that contains the EXE entry point
//
// Modifications:
//  2025-01-08	Created
//  2025-06-16  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/Common.h"
#include "../Inc/GetCurrentPrivilegeLevel.h"
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
extern "C" __declspec(noreturn) VOID __stdcall ExeEntry(
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
	BOOLEAN bSupervisorMode = FALSE;

	// Check processor's CPL
	bSupervisorMode = is_supervisor_mode();
	if (bSupervisorMode) {
		DEBUG_PRINT("supervisor-mode\n");
	}
	else {
		DEBUG_PRINT("user-mode\n");
	}

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