// ========================================================================
// File: ReadControlRegisters.h
//
// Author: winterknife
//
// Description: Header file for ReadControlRegisters.cpp source file
//
// Modifications:
//  2024-10-08	Created
//  2024-10-09  Updated
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
// Structures/Enumerations/Unions
// ========================================================================

#pragma region STRUCTS_ENUMS_UNIONS

#pragma warning(push)
#pragma warning(disable: 4201)
typedef union _CR0_FLAGS {
    struct {
        QWORD PE        : 1;  // Protection Enable
        QWORD MP        : 1;  // Monitor Coprocessor
        QWORD EM        : 1;  // Emulation
        QWORD TS        : 1;  // Task Switched
        QWORD ET        : 1;  // Extension Type
        QWORD NE        : 1;  // Numeric Error
        QWORD Reserved1 : 10; // Reserved
        QWORD WP        : 1;  // Write Protect
        QWORD Reserved2 : 1;  // Reserved
        QWORD AM        : 1;  // Alignment Mask
        QWORD Reserved3 : 10; // Reserved
        QWORD NW        : 1;  // Not Write-through
        QWORD CD        : 1;  // Cache Disable
        QWORD PG        : 1;  // Paging
    };
    QWORD Value;
} CR0_FLAGS, *PCR0_FLAGS;
#pragma warning(pop)

#pragma endregion

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
    _In_ HANDLE hCurrentProcess,
    _In_ HANDLE hCurrentThread,
    _In_ QWORD  qwCurrentPc,
    _In_ DWORD  dwProcessor,
    _In_ PCSTR  strArgs
);

/// @brief Built-in command to display Control Register 0 (CR0) flags
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall readcr0(
    _In_ HANDLE hCurrentProcess,
    _In_ HANDLE hCurrentThread,
    _In_ QWORD  qwCurrentPc,
    _In_ DWORD  dwProcessor,
    _In_ PCSTR  strArgs
);

#pragma endregion