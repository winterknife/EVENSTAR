// ========================================================================
// File: GetCurrentPrivilegeLevel.h
//
// Author: winterknife
//
// Description: Header file for GetCurrentPrivilegeLevel32/64.asm source file
//
// Modifications:
//  2025-06-16	Created
//  2025-06-16  Updated
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
// Assembly routine declarations
// ========================================================================

#pragma region DECLARATIONS

/// @brief Check the Current Privilege Level (CPL) of the processor
/// @param None
/// @return Returns TRUE if CPL < 3 (supervisor-mode) or FALSE if CPL = 3 (user-mode)
_Success_(return != 0) _Must_inspect_result_ _IRQL_requires_max_(HIGH_LEVEL)
extern "C" __declspec(noinline) BOOLEAN __fastcall is_supervisor_mode(
	VOID
);

#pragma endregion