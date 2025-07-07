// ========================================================================
// File: BaseDataTypes.h
//
// Author: winterknife
//
// Description: Type definitions for common Windows base data types made
// for maintaining uniformity across all User Mode and Kernel Mode code
//
// Modifications:
//  2021-07-31	Created
//  2022-08-13	Updated
// ========================================================================

// ========================================================================
// Pragmas
// ========================================================================

#pragma once

// ========================================================================
// Type definitions
// ========================================================================

#pragma region TYPEDEFS

// 8-bit unsigned integer, range = 0 - 255, unsigned char
typedef unsigned __int8 BYTE, *PBYTE;

// 16-bit unsigned integer, range = 0 - 65535, unsigned short
typedef unsigned __int16 WORD, *PWORD;

// 32-bit unsigned integer, range = 0 - 4294967295, unsigned int or unsigned long
typedef unsigned long DWORD, *PDWORD;

// 64-bit unsigned integer, range = 0 - 18446744073709551615, unsigned long long
typedef unsigned __int64 QWORD, *PQWORD;

// Should be TRUE(1) or FALSE(0), unsigned char or bool
typedef unsigned __int8 BOOLEAN, *PBOOLEAN;

// 8-bit UTF-8/Multibyte/ANSI character, char
typedef __int8 CHAR, *PCHAR;

// 16-bit UTF-16/Wide/UNICODE character, unsigned short
typedef wchar_t WCHAR, *PWCHAR;

// Pointer to any type, size = 4 bytes or 8 bytes depending on code bitness
typedef void* PVOID;

// Pointer to a constant of any type
typedef const void* PCVOID;

// Pointer to constant null-terminated string of ANSI characters
typedef _Null_terminated_ const __int8* PCSTR;

// Pointer to constant null-terminated string of UNICODE characters
typedef _Null_terminated_ const wchar_t* PCWSTR;

// Pointer to constant null-terminated string of ANSI or UNICODE characters depending on character encoding scheme
#if defined(UNICODE)
typedef const __wchar_t* PCTSTR;
#else
typedef const __int8* PCTSTR;
#endif

// 32-bit or 64-bit unsigned integer, range = 0 - 4294967295 or 18446744073709551615 depending on compiler bitness
// Used for casting pointers
#if defined(_WIN64)
typedef unsigned __int64 DWORD_PTR, *PDWORD_PTR;
#else
typedef unsigned long DWORD_PTR, *PDWORD_PTR;
#endif

#pragma endregion