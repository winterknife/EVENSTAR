// ========================================================================
// File: DbgExt.cpp
//
// Author: winterknife
//
// Description: Source file that contains the basic template for a
// WdbgExts extension DLL
//
// Modifications:
//  2024-10-08	Created
//  2025-06-23  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/DbgExt.h"

// ========================================================================
// Globals
// ========================================================================

#pragma region GLOBALS

EXT_API_VERSION ApiVersion = { 10, 0, EXT_API_VERSION_NUMBER64, 0 };
WINDBG_EXTENSION_APIS ExtensionApis;
DWORD SavedMajorVersion;
DWORD SavedMinorVersion;

#pragma endregion

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

VOID __stdcall WinDbgExtensionDllInit(
    _In_ PWINDBG_EXTENSION_APIS pWindbgExtensionApis,
    _In_ WORD                   woMajorVersion,
    _In_ WORD                   woMinorVersion
) {
    ExtensionApis = *pWindbgExtensionApis;
    SavedMajorVersion = woMajorVersion;
    SavedMinorVersion = woMinorVersion;
}

LPEXT_API_VERSION __stdcall ExtensionApiVersion(
    VOID
) {
    return &ApiVersion;
}

VOID __stdcall CheckVersion(
    VOID
) {
    return;
}

#pragma endregion