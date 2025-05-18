// ========================================================================
// File: Help.h
//
// Author: winterknife
//
// Description: Header file for Help.cpp source file
//
// Modifications:
//  2025-05-14	Created
//  2025-05-14  Updated
// ========================================================================

// ========================================================================
// Pragmas
// ========================================================================

#pragma once

// ========================================================================
// Includes
// ========================================================================

#include "Common.h"

// ========================================================================
// C routine declarations
// ========================================================================

#pragma region DECLARATIONS

/// @brief Built-in help command for the debugger extension DLL
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall help(
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

#pragma endregion