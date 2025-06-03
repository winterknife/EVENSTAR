// ========================================================================
// File: GetProcessDirectoryTableBase.cpp
//
// Author: winterknife
//
// Description: Source file that contains the necessary routines to find a
// process's DirectoryTableBase using an arbitrary virtual memory read primitive
// and its executive process object
//
// Modifications:
//  2025-05-20	Created
//  2025-05-27  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/GetProcessDirectoryTableBase.h"
#include "../Inc/DbgExt.h"
#include <Shlwapi.h>

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

_Use_decl_annotations_
VOID __stdcall get_process_dtb(
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

    // Init local variables
    QWORD qwEprocessKva = 0;
    QWORD qwUserDirectoryTableBase = 0;

    // Determine if the target uses 64-bit pointers
    if (!IsPtr64()) {
        dprintf("[-] IA-32 target is not supported by this extension!\n");
        goto cleanup;
    }

    // Convert string representation of nt!_EPROCESS pointer to an integer
    if (!StrToInt64ExA(strArgs, STIF_SUPPORT_HEX, (LONGLONG*)&qwEprocessKva)) {
        dprintf("[-] Invalid args!\n");
        goto cleanup;
    }
    dprintf("[*] nt!_EPROCESS KVA=0x%I64X\n", qwEprocessKva);

    // Get the physical address of the first table that is used in virtual address translation for UVAS contained in CR3
    // 1: kd > dt nt!_EPROCESS Pcb
    //    + 0x000 Pcb : _KPROCESS
    // 1: kd > dt nt!_KPROCESS DirectoryTableBase
    //    + 0x028 DirectoryTableBase : Uint8B
    if (!ReadMemory((qwEprocessKva + DIRECTORYTABLEBASE_OFFSET), &qwUserDirectoryTableBase, 0x08, NULL)) {
        dprintf("[-] Error reading virtual memory!\n");
        goto cleanup;
    }
    dprintf("[+] nt!_EPROCESS.Pcb.DirectoryTableBase=0x%I64X\n", qwUserDirectoryTableBase);

    // TO-DO: Handle case when KVA Shadow mitigation is enabled, use nt!_KPROCESS.UserDirectoryTableBase

    // Cleanup
cleanup:
    return;
}

#pragma endregion