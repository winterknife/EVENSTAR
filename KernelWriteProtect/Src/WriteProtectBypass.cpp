// ========================================================================
// File: WriteProtectBypass.cpp
//
// Author: winterknife
//
// Description: Source file that contains the necessary routines to bypass
// the Write Protect (WP) mitigation to allow supervisor-level procedures
// to write into read-only pages
//
// Modifications:
//  2026-05-12	Created
//  2026-05-14  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/WriteProtectBypass.h"

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

_Use_decl_annotations_
VOID __stdcall copy_memory_cr0_wp(
	VOID*       pDestination,
	CONST VOID* pcSource,
	DWORD_PTR   dwptrLength
) {
	// Init local variables
	DWORD dwCurrentProcessorNumber = 0;
	KAFFINITY kaffinityNew = 0;
	KAFFINITY kaffinityOld = 0;
	KIRQL kirqlOld = 0;
	QWORD qwCr4Value = 0;
	BOOLEAN bCetDisabled = false;
	QWORD qwCr0Value = 0;
	BOOLEAN bWpDisabled = false;

	// Get the current processor number
	dwCurrentProcessorNumber = KeGetCurrentProcessorNumber();

	// Set a processor affinity mask for the current thread
	// This will lock the current thread to the logical processor it is running on (CPU pinning)
	kaffinityNew = __ll_lshift(0x1, static_cast<int>(dwCurrentProcessorNumber));
	kaffinityOld = KeSetSystemAffinityThreadEx(kaffinityNew);

	// Raise the Interrupt Request Level (IRQL) of the current processor to the highest level
	// This will prevent the thread scheduler from preempting the current thread
	KeRaiseIrql(HIGH_LEVEL, &kirqlOld);

	// Disable interrupts by clearing the RFLAGS.IF bit
	// This will prevent the current processor from servicing any maskable interrupts
	_disable(); // CLI - Clear Interrupt Flag

	// Read the CR4 register value
	qwCr4Value = __readcr4();

	// Clear the CR4.CET bit
	// CR0.WP cannot be cleared as long as CR4.CET is set
	// WARNING: HyperGuard / Secure Kernel Patch Guard (SKPG) intercepts writes to CR0 and CR4 registers
	bCetDisabled = _bittestandreset64(reinterpret_cast<LONG64*>(&qwCr4Value), 23LL);
	__writecr4(qwCr4Value);

	// Read the CR0 register value
	qwCr0Value = __readcr0();

	// Clear the CR0.WP bit
	// When clear, it allows kernel-mode code to write into read-only pages
	bWpDisabled = _bittestandreset64(reinterpret_cast<LONG64*>(&qwCr0Value), 16LL);
	__writecr0(qwCr0Value);

	// Write into RO pages
	__movsb(static_cast<PUCHAR>(pDestination), static_cast<UCHAR const*>(pcSource), dwptrLength);

	// Set the CR0.WP bit if it was cleared before
	// When set, it inhibits kernel-mode code from writing into read-only pages
	if (bWpDisabled) {
		_bittestandset64(reinterpret_cast<LONG64*>(&qwCr0Value), 16LL);
		__writecr0(qwCr0Value);
	}

	// Set the CR4.CET bit if it was cleared before
	// This flag can be set only if CR0.WP is set
	if (bCetDisabled) {
		_bittestandset64(reinterpret_cast<LONG64*>(&qwCr4Value), 23LL);
		__writecr4(qwCr4Value);
	}

	// Enable interrupts by setting the RFLAGS.IF bit
	_enable(); // STI - Set Interrupt Flag

	// Restore the original IRQL of the current processor
	KeLowerIrql(kirqlOld);

	// Restore the original processor affinity mask for the current thread
	KeRevertToUserAffinityThreadEx(kaffinityOld);
}

_Use_decl_annotations_
VOID __stdcall copy_memory_double_mapping(
	VOID*       pDestination,
	CONST VOID* pcSource,
	DWORD_PTR   dwptrLength
) {
	// Init local variables
	PMDL pMdl = nullptr;
	BOOLEAN bLocked = false;
	PVOID pBufferKva = nullptr;
	NTSTATUS status = STATUS_SUCCESS;

	// Allocate a MDL for the read-only destination memory block in KVAS
	pMdl = IoAllocateMdl(pDestination, static_cast<ULONG>(dwptrLength), false, false, nullptr);
	if (pMdl == nullptr) {
		goto cleanup;
	}

	// Lock the pages in the MDL
	__try {
		MmProbeAndLockPages(pMdl, KernelMode, IoReadAccess);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		goto cleanup;
	}

	bLocked = true;

	// Map the locked pages into KVAS effectively creating a second read-write mapping of the same physical memory
	pBufferKva = MmMapLockedPagesSpecifyCache(pMdl, KernelMode, MmCached, nullptr, false, HighPagePriority | MdlMappingNoExecute);
	if (pBufferKva == nullptr) {
		goto cleanup;
	}

	// Set the protection type for the double mapping to RW
	status = MmProtectMdlSystemAddress(pMdl, PAGE_READWRITE);
	if (!NT_SUCCESS(status)) {
		goto cleanup;
	}

	// Write into RW pages
	// WARNING: If the page is protected by KDP then it will be marked as read-only in the SLAT entry
	__movsb(static_cast<PUCHAR>(pBufferKva), static_cast<UCHAR const*>(pcSource), dwptrLength);

	// Cleanup
cleanup:
	// Release the double mapping
	if (pBufferKva)
		MmUnmapLockedPages(pBufferKva, pMdl);

	// Unlock the pages in the MDL
	if (bLocked)
		MmUnlockPages(pMdl);

	// Release the MDL
	if (pMdl)
		IoFreeMdl(pMdl);
}

#pragma endregion