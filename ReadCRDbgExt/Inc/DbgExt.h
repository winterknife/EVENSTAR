// ========================================================================
// File: DbgExt.h
//
// Author: winterknife
//
// Description: Header file for DbgExt.cpp source file
//
// Modifications:
//  2024-10-08	Created
//  2024-10-08  Updated
// ========================================================================

// ========================================================================
// Pragmas
// ========================================================================

#pragma once

// ========================================================================
// Includes
// ========================================================================

#include "Common.h"
#define KDEXT_64BIT
#include <WDBGEXTS.H>
#include <ntverp.h>

// ========================================================================
// C routine declarations
// ========================================================================

#pragma region DECLARATIONS

/// @brief Load and initialize the extension module
/// @param pWindbgExtensionApis Pointer to WINDBG_EXTENSION_APIS64 structure
/// @param woMajorVersion Specifies the Microsoft Windows build type
/// @param woMinorVersion Specifies the Windows build number of the target system
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall WinDbgExtensionDllInit(
    _In_ PWINDBG_EXTENSION_APIS pWindbgExtensionApis,
    _In_ WORD                   woMajorVersion,
    _In_ WORD                   woMinorVersion
);

/// @brief Returns version information about the extension DLL
/// @param None
/// @return Pointer to EXT_API_VERSION structure
extern "C" __declspec(dllexport) LPEXT_API_VERSION __stdcall ExtensionApiVersion(
    VOID
);

/// @brief Verifies that the extension module version matches the debugger version, and outputs a warning message if there is a mismatch
/// @param None
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall CheckVersion(
    VOID
);

#pragma endregion