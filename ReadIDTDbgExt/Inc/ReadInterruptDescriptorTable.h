// ========================================================================
// File: ReadInterruptDescriptorTable.h
//
// Author: winterknife
//
// Description: Header file for ReadInterruptDescriptorTable.cpp source file
//
// Modifications:
//  2025-06-23	Created
//  2025-06-28  Updated
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

// Interrupt Descriptor Table Register (IDTR)
#pragma pack(push, 1)
typedef struct _IDTR {
    WORD  Limit;
    QWORD BaseAddress;
} IDTR, *PIDTR;
#pragma pack(pop)

// Interrupt/Trap Gate
#pragma warning(push)
#pragma warning(disable: 4201)
#pragma pack(push, 1)
typedef struct _INTERRUPT_TRAP_GATE_DESCRIPTOR {
    WORD OffsetLow;         // bits 00 - 15
    WORD SegmentSelector;   // bits 16 - 31
    struct {
        WORD IST       : 3; // bits 32 - 34 (Interrupt Stack Table)
        WORD Reserved1 : 5; // bits 35 - 39 (0)
        WORD Type      : 4; // bits 40 - 43
        WORD Reserved2 : 1; // bit 44 (0)
        WORD DPL       : 2; // bits 45 - 46 (Descriptor Privilege Level)
        WORD P         : 1; // bit 47 (Segment Present flag)
    };
    WORD  OffsetMiddle;     // bits 48 - 63
    DWORD OffsetHigh;       // bits 64 - 95
    DWORD Reserved3;        // bits 96 - 127 (0)
} INTERRUPT_TRAP_GATE_DESCRIPTOR, *PINTERRUPT_TRAP_GATE_DESCRIPTOR;
#pragma pack(pop)
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
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

/// @brief Built-in command to read and parse the gate descriptors in the Interrupt Descriptor Table (IDT)
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall read_idt(
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

#pragma endregion