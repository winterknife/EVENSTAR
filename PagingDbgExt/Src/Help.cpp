// ========================================================================
// File: Help.cpp
//
// Author: winterknife
//
// Description: Source file that contains the implementation of the built-in
// help command for the debugger extension DLL
//
// Modifications:
//  2025-05-14	Created
//  2025-05-18  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/Help.h"
#include "../Inc/DbgExt.h"

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

_Use_decl_annotations_
VOID __stdcall help(
    HANDLE hCurrentProcess,
    HANDLE hCurrentThread,
    QWORD  qwCurrentPc,
    DWORD  dwProcessor,
    PCSTR  strArgs
) {
    UNREFERENCED_PARAMETER(hCurrentProcess);
    UNREFERENCED_PARAMETER(hCurrentThread);
    UNREFERENCED_PARAMETER(qwCurrentPc);
    UNREFERENCED_PARAMETER(dwProcessor);
    UNREFERENCED_PARAMETER(strArgs);

    dprintf(
        "Help for debugger extension DLL PagingDbgExt.dll\n"
        "   help           - Show help menu\n"
        "   get_kernel_dtb - Find the kernel's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for KVAS contained in CR3 from the Low Stub\n"
    );
}

#pragma endregion