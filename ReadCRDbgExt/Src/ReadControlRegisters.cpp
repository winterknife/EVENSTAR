// ========================================================================
// File: ReadControlRegisters.cpp
//
// Author: winterknife
//
// Description: Source file that contains the necessary routines to display
// various flags of the Control Registers of the target system
//
// Modifications:
//  2024-10-08	Created
//  2024-10-09  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/ReadControlRegisters.h"
#include "../Inc/DbgExt.h"

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

VOID __stdcall help(
    _In_ HANDLE hCurrentProcess,
    _In_ HANDLE hCurrentThread,
    _In_ QWORD  qwCurrentPc,
    _In_ DWORD  dwProcessor,
    _In_ PCSTR  strArgs
) {
    UNREFERENCED_PARAMETER(hCurrentProcess);
    UNREFERENCED_PARAMETER(hCurrentThread);
    UNREFERENCED_PARAMETER(qwCurrentPc);
    UNREFERENCED_PARAMETER(dwProcessor);
    UNREFERENCED_PARAMETER(strArgs);

    dprintf(
        "Help for debugger extension DLL ReadCRDbgExt.dll\n"
        "   help    - Show help menu\n"
        "   readcr0 - Display CR0 flags\n"
        "   readcr4 - Display CR4 flags\n"
    );
}

VOID __stdcall readcr0(
    _In_ HANDLE hCurrentProcess,
    _In_ HANDLE hCurrentThread,
    _In_ QWORD  qwCurrentPc,
    _In_ DWORD  dwProcessor,
    _In_ PCSTR  strArgs
) {
    UNREFERENCED_PARAMETER(hCurrentProcess);
    UNREFERENCED_PARAMETER(hCurrentThread);
    UNREFERENCED_PARAMETER(qwCurrentPc);
    UNREFERENCED_PARAMETER(strArgs);

    dprintf("[!] Current processor number = %d\n", dwProcessor);

    // Init local variables
    BOOLEAN bEvaluated = FALSE;
    QWORD qwCR0 = 0;
    CR0_FLAGS cr0Flags; ZERO_MEMORY(&cr0Flags, sizeof(CR0_FLAGS));

    // Determine if the target uses 64-bit pointers
    if (!IsPtr64()) {
        dprintf("[-] IA-32 target is not supported by this extension!\n");
        goto cleanup;
    }

    // Read CR0 value
    bEvaluated = (BOOLEAN)GetExpressionEx("@cr0", &qwCR0, NULL);
    if (!bEvaluated) {
        dprintf("[-] Error evaluating MASM expression!\n");
        goto cleanup;
    }
    dprintf("[+] CR0 = 0x%I64X\n", qwCR0);

    // Display CR0 flags
    dprintf(
        "    |-----|------|--------|\n"
        "    | %-3s | %-4s | %-6s |\n"
        "    |-----|------|--------|\n",
        "Bit", "Flag", "Status"
    );

    cr0Flags.Value = qwCR0;

    dprintf(
        "    | %3d | %4s | %6d |\n",
        0,
        "PE",
        cr0Flags.PE
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        1,
        "MP",
        cr0Flags.MP
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        2,
        "EM",
        cr0Flags.EM
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        3,
        "TS",
        cr0Flags.TS
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        4,
        "ET",
        cr0Flags.ET
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        5,
        "NE",
        cr0Flags.NE
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        16,
        "WP",
        cr0Flags.WP
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        18,
        "AM",
        cr0Flags.AM
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        29,
        "NW",
        cr0Flags.NW
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        30,
        "CD",
        cr0Flags.CD
    );
    dprintf(
        "    | %3d | %4s | %6d |\n",
        31,
        "PG",
        cr0Flags.PG
    );

    dprintf("    |-----|------|--------|\n");

cleanup:
    return;
}

VOID __stdcall readcr4(
    _In_ HANDLE hCurrentProcess,
    _In_ HANDLE hCurrentThread,
    _In_ QWORD  qwCurrentPc,
    _In_ DWORD  dwProcessor,
    _In_ PCSTR  strArgs
) {
    UNREFERENCED_PARAMETER(hCurrentProcess);
    UNREFERENCED_PARAMETER(hCurrentThread);
    UNREFERENCED_PARAMETER(qwCurrentPc);
    UNREFERENCED_PARAMETER(strArgs);

    dprintf("[!] Current processor number = %d\n", dwProcessor);

    // Init local variables
    BOOLEAN bEvaluated = FALSE;
    QWORD qwCR4 = 0;
    CR4_FLAGS cr4Flags; ZERO_MEMORY(&cr4Flags, sizeof(CR4_FLAGS));

    // Determine if the target uses 64-bit pointers
    if (!IsPtr64()) {
        dprintf("[-] IA-32 target is not supported by this extension!\n");
        goto cleanup;
    }

    // Read CR4 value
    bEvaluated = (BOOLEAN)GetExpressionEx("@cr4", &qwCR4, NULL);
    if (!bEvaluated) {
        dprintf("[-] Error evaluating MASM expression!\n");
        goto cleanup;
    }
    dprintf("[+] CR4 = 0x%I64X\n", qwCR4);

    // Display CR4 flags
    dprintf(
        "    |-----|------------|--------|\n"
        "    | %-3s | %-10s | %-6s |\n"
        "    |-----|------------|--------|\n",
        "Bit", "Flag", "Status"
    );

    cr4Flags.Value = qwCR4;

    dprintf(
        "    | %3d | %10s | %6d |\n",
        0,
        "VME",
        cr4Flags.VME
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        1,
        "PVI",
        cr4Flags.PVI
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        2,
        "TSD",
        cr4Flags.TSD
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        3,
        "DE",
        cr4Flags.DE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        4,
        "PSE",
        cr4Flags.PSE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        5,
        "PAE",
        cr4Flags.PAE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        6,
        "MCE",
        cr4Flags.MCE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        7,
        "PGE",
        cr4Flags.PGE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        8,
        "PCE",
        cr4Flags.PCE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        9,
        "OSFXSR",
        cr4Flags.OSFXSR
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        10,
        "OSXMMEXCPT",
        cr4Flags.OSXMMEXCPT
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        11,
        "UMIP",
        cr4Flags.UMIP
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        12,
        "LA57",
        cr4Flags.LA57
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        13,
        "VMXE",
        cr4Flags.VMXE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        14,
        "SMXE",
        cr4Flags.SMXE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        16,
        "FSGSBASE",
        cr4Flags.FSGSBASE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        17,
        "PCIDE",
        cr4Flags.PCIDE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        18,
        "OSXSAVE",
        cr4Flags.OSXSAVE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        19,
        "KL",
        cr4Flags.KL
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        20,
        "SMEP",
        cr4Flags.SMEP
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        21,
        "SMAP",
        cr4Flags.SMAP
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        22,
        "PKE",
        cr4Flags.PKE
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        23,
        "CET",
        cr4Flags.CET
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        24,
        "PKS",
        cr4Flags.PKS
    );
    dprintf(
        "    | %3d | %10s | %6d |\n",
        25,
        "UINTR",
        cr4Flags.UINTR
    );

    dprintf("    |-----|------------|--------|\n");

cleanup:
    return;
}

#pragma endregion