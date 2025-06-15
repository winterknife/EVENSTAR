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
//  2025-06-15  Updated
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
        "   help                      - Show help menu\n"
        "   get_kernel_dtb            - Find the kernel's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for KVAS contained in CR3 from the Low Stub\n"
        "   get_process_dtb           - Find a process's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for UVAS contained in CR3 from the EPROCESS structure\n"
        "   check_4_level_paging_mode - Check if the logical processor is using 4-level IA-32e paging mode\n"
        "   get_pml4_autoentry_index  - Find the self-reference entry/auto-entry index of the Page Map Level 4 (PML4) table from the CR3\n"
        "   get_pxe_base              - Compute the starting KVA of the paging structure entry (PxE) range from the PML4 table auto-entry index\n"
        "   get_pxe_address           - Compute the KVA of the paging structure entry (PxE) that maps the specified VA from the PML4 table auto-entry index\n"
        "   get_physical_address      - Translate the specified linear address (VA) to its mapped physical address (PA) and determine the VA's access rights from the CR3\n"
    );
}

#pragma endregion