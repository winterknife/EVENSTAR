// ========================================================================
// File: Common.h
//
// Author: winterknife
//
// Description: Contains the common stuff for this project
//
// Modifications:
//  2021-08-21	Created
//  2025-07-05	Updated
// ========================================================================

// ========================================================================
// Pragmas
// ========================================================================

#pragma once

// Specify program entry point
#pragma comment(linker, "/ENTRY:ExeEntry")

// Merge sections
#if defined (_MSC_VER)
#if (_MSC_VER >= 1920)
#pragma comment(linker, "/MERGE:_RDATA=.rdata")
#endif
#endif

// Emit error message at compile time if trying to build for 32-bit x86 target
#if !defined(_WIN64)
#error x86 build target is unsupported!
#endif

// ========================================================================
// Includes
// ========================================================================

#define WIN32_LEAN_AND_MEAN
#define _NO_CRT_STDIO_INLINE
#include <Windows.h>
#include <intrin.h>
#include <stdio.h>
#include "BaseDataTypes.h"

#pragma intrinsic(__stosb)
#pragma intrinsic(__movsb)
#pragma intrinsic(strlen)
#pragma intrinsic(strcmp)

// ========================================================================
// Macros
// ========================================================================

#pragma region MACROS

// Module name
#define __MODULE__ "GetCurrentProcessorNumber"

// Comment out for final build
#define DEBUG_BUILD

// Print debug message macro
#ifdef DEBUG_BUILD
#define STRIP(...) __VA_ARGS__
#define DEBUG_PREFIX "[DBG]: "
#define DEBUG_PRINT(_x_, ...) printf(DEBUG_PREFIX _x_, ##__VA_ARGS__);
#else
#define DEBUG_PRINT(_x_, ...) void(0)
#endif

// Stringizing operator macro
#ifndef _CRT_STRINGIZE
#define _CRT_STRINGIZE_(x) #x
#define _CRT_STRINGIZE(x) _CRT_STRINGIZE_(x)
#endif

// Get mangled name of a function
#define GET_MANGLED_FUNCTION_NAME __pragma(message(__FILE__ _CRT_STRINGIZE((__LINE__): \nfunction:\t) __FUNCSIG__ " is mangled to: " __FUNCDNAME__))

// To set alternate name of decorated x86 IAT global function pointer
#ifdef _X86_
// Uses undocumented /ALTERNATENAME linker flag
#define ALT_NAME(name, n) __pragma(comment(linker, _CRT_STRINGIZE(/ALTERNATENAME:__imp__##name##@##n####=___imp_##name)))
#else
#define ALT_NAME(name, n)
#endif

// To declare/initialize global IAT function pointers for run-time dynamic linking, use on global scope
#define IMP_FUNC(name, n) EXTERN_C_START PVOID __imp_##name = NULL; EXTERN_C_END ALT_NAME(name, n)

// To declare/initialize local function pointers for run-time dynamic linking, use on local scope
// Warning: will ignore SAL annotations
#define IMP_FUNC_PIC(name) typedef decltype(name) __type_##name; __type_##name* ##name = NULL;

// Check if a function is in a delay loaded module, use on a global scope
#define CHECK_DELAY_LOAD(f) extern "C" extern void* __imp_load_ ##f; void test_delay_load ##f(){ (__imp_load_ ##f) ? 1 : 0; }

// Macro to indicate a specific function to the linker as the first in the link order
#define CODE_BEGIN code_seg(push, ".text")

// Macro to indicate the end of the specific function to the linker
#define CODE_END code_seg(pop)

// Macro to disable all compiler optimizations for a specific function
#define OPTIMIZATION_OFF optimize("", off)

// Macro to re-enable/reset compiler optimizations for a specific function
#define OPTIMIZATION_ON optimize("", on)

// Macro to enable compiler optimizations for generating short sequences of machine code for a specific function
#if defined(_M_IX86)
#define OPTIMIZATION_SIZE optimize("gsy", on)
#else
#define OPTIMIZATION_SIZE optimize("gs", on)
#endif

// Macro to enable compiler optimizations for generating fast sequences of machine code for a specific function
#if defined(_M_IX86)
#define OPTIMIZATION_SPEED optimize("gty", on)
#else
#define OPTIMIZATION_SPEED optimize("gt", on)
#endif

// Macro to fill a block of memory with zeroes given it's address and length in bytes by generating store string instruction (rep stosb)
// Enhanced REP STOSB/MOVSB (ERMSB) are only available since Ivy Bridge Intel microarchitecture (2012/2013)
// Processors that provide support for enhanced MOVSB/STOSB operations are enumerated by the CPUID feature flag: CPUID:(EAX=7H, ECX=0H):EBX.ERMSB[bit 9] = 1
#define ZERO_MEMORY(Destination, Length) __stosb((PBYTE)Destination, 0, Length)

// Macro to copy a block of memory given it's source address, destination address and the number of bytes to copy by generating move string instruction (rep movsb)
#define COPY_MEMORY(Destination, Source, Count) __movsb((PBYTE)Destination, (const PBYTE)Source, Count)

#pragma endregion

// ========================================================================
// C inline routines
// ========================================================================

#pragma region INLINES

/// @brief To compare two blocks of memory and return the number of bytes that match
/// @param pcSource1 Pointer to the first block of memory
/// @param pcSource2 Pointer to the second block of memory
/// @param dwptrLength The number of bytes to compare
/// @return Number of bytes in the two blocks that match, if all bytes match up to the specified Length value, the Length value is returned
extern "C" __forceinline DWORD_PTR __stdcall compare_memory(_In_ const PVOID pcSource1, _In_ const PVOID pcSource2, _In_ DWORD_PTR dwptrLength) {
	// Init local variables
	DWORD_PTR dwptrIndex = 0;

	// Start comparing the two blocks of memory
	for (dwptrIndex = 0; (dwptrIndex < dwptrLength) && (((PBYTE)pcSource1)[dwptrIndex] == ((PBYTE)pcSource2)[dwptrIndex]); dwptrIndex++);

	return dwptrIndex;
}

#pragma endregion