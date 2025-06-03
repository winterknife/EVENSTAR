// ========================================================================
// File: GetProcessDirectoryTableBase.h
//
// Author: winterknife
//
// Description: Header file for GetProcessDirectoryTableBase.cpp source file
//
// Modifications:
//  2025-05-20	Created
//  2025-05-24  Updated
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
// Macros
// ========================================================================

#pragma region MACROS

#define DIRECTORYTABLEBASE_OFFSET 0x28

#pragma endregion

// ========================================================================
// C routine declarations
// ========================================================================

#pragma region DECLARATIONS

/// @brief Built-in command to find a process's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for UVAS contained in CR3 from the EPROCESS structure
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments (address of executive process object of the target process)
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall get_process_dtb(
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

#pragma endregion