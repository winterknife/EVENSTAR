// ========================================================================
// File: DllMain.cpp
//
// Author: winterknife
//
// Description: Source file that contains the DLL entry point
//
// Modifications:
//  2024-10-08	Created
//  2024-10-08  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/Common.h"

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

#pragma CODE_BEGIN
/// @brief DLL entry point
/// @param hModule A handle to the DLL module
/// @param dwReason The reason code that indicates why the DLL entry-point function is being called
/// @param dwReserved Reserved
/// @return TRUE if DLL initialization succeeds or FALSE if it fails
extern "C" __declspec(noinline) BOOLEAN __stdcall DllInit(
	_In_     HMODULE hModule,
	_In_     DWORD   dwReason,
	_In_opt_ DWORD   dwReserved
) {
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(dwReserved);
	
	switch (dwReason) {
	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;

	case DLL_PROCESS_ATTACH:
		break;
	}

	return TRUE;
}
#pragma CODE_END

#pragma endregion