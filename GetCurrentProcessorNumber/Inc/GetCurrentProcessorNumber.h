// ========================================================================
// File: GetCurrentProcessorNumber.h
//
// Author: winterknife
//
// Description: Header file for GetCurrentProcessorNumber.cpp source file
//
// Modifications:
//  2025-07-01	Created
//  2025-07-06  Updated
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

#if defined(_M_X64)
#define KGDT_R3_TEB 0x50
#elif defined(_M_IX86)
#define KGDT_R3_TEB 0x38
#endif

#define RPL_MASK    0x03

#pragma endregion

// ========================================================================
// Structures/Enumerations/Unions
// ========================================================================

#pragma region STRUCTS_ENUMS_UNIONS

// CPUID structure for using the return data of CPUID in the application
typedef struct _CPUID_REGISTERS {
    DWORD dwEAX;
    DWORD dwEBX;
    DWORD dwECX;
    DWORD dwEDX;
} CPUID_REGISTERS, *PCPUID_REGISTERS;

#pragma endregion

// ========================================================================
// C routine declarations
// ========================================================================

#pragma region DECLARATIONS

/// @brief Retrieve the number of the logical processor on which the calling thread is running
/// @param None
/// @return Returns the current processor number (only valid for systems with fewer than 64 logical processors - processor group 0)
_Success_(return != -1) _Must_inspect_result_ _IRQL_requires_max_(HIGH_LEVEL)
extern "C" __declspec(noinline) DWORD __stdcall get_current_processor_number(
	VOID
);

#pragma endregion