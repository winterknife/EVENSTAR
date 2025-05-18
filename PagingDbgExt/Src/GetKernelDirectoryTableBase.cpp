// ========================================================================
// File: GetKernelDirectoryTableBase.cpp
//
// Author: winterknife
//
// Description: Source file that contains the necessary routines to find the
// kernel's DirectoryTableBase using an arbitrary physical memory read primitive
// to locate the Low Stub with heuristic scanning
//
// Modifications:
//  2025-05-13	Created
//  2025-05-18  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/GetKernelDirectoryTableBase.h"
#include "../Inc/DbgExt.h"

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

_Use_decl_annotations_
VOID __stdcall get_kernel_dtb(
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

    // Init local variables
    PVOID pBuffer = NULL;
    DWORD dwActiveProcessorCount = 0;
    QWORD qwPhysicalAddress = 0;
    DWORD dwBytesRead = 0;
    PPROCESSOR_START_BLOCK pProcessorStartBlock = NULL;
    QWORD qwKernelDirectoryTableBase = 0;

    // Determine if the target uses 64-bit pointers
    if (!IsPtr64()) {
        dprintf("[-] IA-32 target is not supported by this extension!\n");
        goto cleanup;
    }

    // Allocate 0x1000 (PAGE_SIZE_4KB) bytes worth of heap memory to read the Low Stub
    pBuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0x1000);
    if (pBuffer == NULL) {
        dprintf("[-] Error allocating heap memory!\n");
        goto cleanup;
    }

    // This technique of finding the Low Stub doesn't work if the number of Application Processors (APs) == 1
    // This happens because the nt!_PROCESSOR_START_BLOCK structure is filled incorrectly in this case
    // Get nt!_KUSER_SHARED_DATA.ActiveProcessorCount
    if (!ReadMemory((KUSER_SHARED_DATA_RO_MAPPING_X64_KVA + ACTIVEPROCESSORCOUNT_OFFSET), &dwActiveProcessorCount, 0x04, NULL)) {
        dprintf("[-] Error reading virtual memory!\n");
        goto cleanup;
    }

    // Check nt!_KUSER_SHARED_DATA.ActiveProcessorCount
    if (dwActiveProcessorCount < 2) {
        dprintf("[-] This technique does not work for UniProcessor (UP) systems!\n");
        goto cleanup;
    }

    // Locate the Low Stub with heuristic scanning
    // The Low Stub is always present on x86 APIC systems in one of the physical pages in the range starting at 0x1000 (4 KB) and less than 0x100000 (1 MB)
    // It is a piece of 16-bit code that aids in CPU mode transitions (Real Mode to Protected Mode to Long Mode) on boot or waking up from S2 and S3 sleeps
    // nt!HalpLowStub contains the KVA of nt!_PROCESSOR_START_BLOCK structure
    // nt!HalpLowStubPhysicalAddress contains the PA of nt!_PROCESSOR_START_BLOCK structure
    for (qwPhysicalAddress = 0x1000; qwPhysicalAddress < 0x100000; qwPhysicalAddress += 0x1000) {
        ReadPhysical(qwPhysicalAddress, pBuffer, 0x1000, &dwBytesRead);
        if (dwBytesRead != 0x1000) {
            dprintf("[-] Error reading physical memory!\n");
            goto cleanup;
        }

        // Low Stub is the nt!_PROCESSOR_START_BLOCK structure
        pProcessorStartBlock = (PPROCESSOR_START_BLOCK)pBuffer;

        // nt!_PROCESSOR_START_BLOCK structure starts with the following bytes decoded as the JMP rel16 instruction:
        // E9 4D 06    jmp 0x650
        // This piece of 16-bit x86 code jumps to the end of the nt!_PROCESSOR_START_BLOCK structure
        // The size of this structure is 0x650/0n1616 bytes starting from Windows 10 1703 Creators Update (RS2) Build 15063
        if (pProcessorStartBlock->Jmp.OpCode != 0xE9)
            continue;

        if (pProcessorStartBlock->Jmp.Offset != 0x06)
            continue;

        // nt!_PROCESSOR_START_BLOCK.CompletionFlag should be set when the Application Processor (AP) has been initialized
        if (pProcessorStartBlock->CompletionFlag != 1)
            continue;

        // nt!_PROCESSOR_START_BLOCK.LmTarget should point to nt!HalpLMStub
        if (pProcessorStartBlock->LmTarget == 0)
            continue;

        // nt!_PROCESSOR_START_BLOCK.ProcessorState.SpecialRegisters.Cr3 should not be zero
        if (pProcessorStartBlock->ProcessorState.SpecialRegisters.Cr3 == 0)
            continue;

        // Found!
        dprintf("[+] nt!_PROCESSOR_START_BLOCK structure found at PA=0x%I64X\n", qwPhysicalAddress);

        // Get the base address of the HAL Heap which is pointed to by nt!HalpOriginalHeapStart
        dprintf("[+] HAL Heap base KVA=0x%I64X\n", ((QWORD)(pProcessorStartBlock->SelfMap) & 0xFFFFFFFFF0000000));

        // Get the physical address of the first table that is used in virtual address translation for KVAS contained in CR3
        qwKernelDirectoryTableBase = pProcessorStartBlock->ProcessorState.SpecialRegisters.Cr3;
        dprintf("[+] nt!_PROCESSOR_START_BLOCK.ProcessorState.SpecialRegisters.Cr3=0x%I64X\n", qwKernelDirectoryTableBase);

        break;
    }

    // Cleanup
cleanup:
    if (pBuffer)
        HeapFree(GetProcessHeap(), 0, pBuffer);

    return;
}

#pragma endregion