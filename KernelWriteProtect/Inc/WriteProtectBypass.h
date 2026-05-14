// ========================================================================
// File: WriteProtectBypass.h
//
// Author: winterknife
//
// Description: Header file for WriteProtectBypass.cpp source file
//
// Modifications:
//  2026-05-12	Created
//  2026-05-14  Updated
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

/// @brief Copies the contents of a source memory block to a destination memory block with write protect bypass using CR0.WP manipulation
/// @param pDestination Pointer to the destination memory block to copy the bytes to
/// @param pcSource Pointer to the source memory block to copy the bytes from
/// @param dwptrLength Number of bytes to copy from the source to the destination
_IRQL_requires_max_(DISPATCH_LEVEL)
EXTERN_C DECLSPEC_NOINLINE VOID __stdcall copy_memory_cr0_wp(
	_Out_writes_bytes_all_(dwptrLength) VOID*       pDestination,
	_In_reads_bytes_(dwptrLength)       CONST VOID* pcSource,
	_In_                                DWORD_PTR   dwptrLength
);

/// @brief Copies the contents of a source memory block to a destination memory block with write protect bypass using double mapping
/// @param pDestination Pointer to the destination memory block to copy the bytes to
/// @param pcSource Pointer to the source memory block to copy the bytes from
/// @param dwptrLength Number of bytes to copy from the source to the destination
_IRQL_requires_max_(DISPATCH_LEVEL)
EXTERN_C DECLSPEC_NOINLINE VOID __stdcall copy_memory_double_mapping(
	_Out_writes_bytes_all_(dwptrLength) VOID*       pDestination,
	_In_reads_bytes_(dwptrLength)       CONST VOID* pcSource,
	_In_                                DWORD_PTR   dwptrLength
);

#pragma endregion