// ========================================================================
// File: ReadMsw.h
//
// Author: winterknife
//
// Description: Header file for ReadMsw32/64.asm source file
//
// Modifications:
//  2025-01-09	Created
//  2025-01-09  Updated
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

/// @brief Check if segment-level protection is enabled
/// @param None
/// @return Returns TRUE if protected mode is enabled or FALSE if real-address mode is enabled
_Success_(return != 0) _Must_inspect_result_ _IRQL_requires_max_(DISPATCH_LEVEL)
extern "C" __declspec(noinline) BOOLEAN __fastcall is_protected_mode_enabled(
	VOID
);

#pragma endregion