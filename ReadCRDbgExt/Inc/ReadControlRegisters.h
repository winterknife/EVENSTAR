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

typedef union _CR4_FLAGS {
    struct {
        QWORD VME        : 1; // Virtual-8086 Mode Extensions
        QWORD PVI        : 1; // Protected-Mode Virtual Interrupts
        QWORD TSD        : 1; // Time Stamp Disable
        QWORD DE         : 1; // Debugging Extensions
        QWORD PSE        : 1; // Page Size Extensions
        QWORD PAE        : 1; // Physical Address Extension
        QWORD MCE        : 1; // Machine-Check Enable
        QWORD PGE        : 1; // Page Global Enable
        QWORD PCE        : 1; // Performance-Monitoring Counter Enable
        QWORD OSFXSR     : 1; // Operating System Support for FXSAVE and FXRSTOR instructions
        QWORD OSXMMEXCPT : 1; // Operating System Support for Unmasked SIMD Floating-Point Exceptions
        QWORD UMIP       : 1; // User-Mode Instruction Prevention
        QWORD LA57       : 1; // 57-bit linear addresses
        QWORD VMXE       : 1; // VMX-Enable Bit
        QWORD SMXE       : 1; // SMX-Enable Bit
        QWORD Reserved1  : 1; // Reserved
        QWORD FSGSBASE   : 1; // FSGSBASE-Enable Bit
        QWORD PCIDE      : 1; // PCID-Enable Bit
        QWORD OSXSAVE    : 1; // XSAVE and Processor Extended States-Enable Bit
        QWORD KL         : 1; // Key-Locker-Enable Bit
        QWORD SMEP       : 1; // SMEP-Enable Bit
        QWORD SMAP       : 1; // SMAP-Enable Bit
        QWORD PKE        : 1; // Enable protection keys for user-mode pages
        QWORD CET        : 1; // Control-flow Enforcement Technology
        QWORD PKS        : 1; // Enable protection keys for supervisor-mode pages
        QWORD UINTR      : 1; // User Interrupts Enable Bit
    };
    QWORD Value;
} CR4_FLAGS, *PCR4_FLAGS;
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

/// @brief Built-in command to display Control Register 4 (CR4) flags
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall readcr4(
    _In_ HANDLE hCurrentProcess,
    _In_ HANDLE hCurrentThread,
    _In_ QWORD  qwCurrentPc,
    _In_ DWORD  dwProcessor,
    _In_ PCSTR  strArgs
);

#pragma endregion