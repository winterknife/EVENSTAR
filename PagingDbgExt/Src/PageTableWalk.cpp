// ========================================================================
// File: PageTableWalk.cpp
//
// Author: winterknife
//
// Description: Source file that contains the necessary routines to walk the
// paging structures using an arbitrary physical memory read primitive to
// translate a Virtual Address (VA) to its Physical Address (PA)
// using Intel 4-level ordinary paging
//
// Modifications:
//  2025-05-20	Created
//  2025-06-03  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/PageTableWalk.h"
#include "../Inc/DbgExt.h"
#include <Shlwapi.h>

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

_Use_decl_annotations_
BOOLEAN __stdcall check_4_level_paging_mode(
	HANDLE hCurrentProcess,
	HANDLE hCurrentThread,
	QWORD  qwCurrentPc,
	DWORD  dwProcessor,
	PCSTR  strArgs
) {
	UNREFERENCED_PARAMETER(hCurrentProcess);
	UNREFERENCED_PARAMETER(hCurrentThread);
	UNREFERENCED_PARAMETER(qwCurrentPc);
	UNREFERENCED_PARAMETER(strArgs);

	dprintf("[!] Current processor number = %d\n", dwProcessor);

	// Init local variables
	BOOLEAN bFlag = FALSE;
	QWORD qwCR0 = 0;
	QWORD qwCR4 = 0;
	QWORD qwIa32Efer = 0;

	// Determine if the target uses 64-bit pointers
	if (!IsPtr64()) {
		dprintf("[-] IA-32 target is not supported by this extension!\n");
		goto cleanup;
	}

	// Read CR0 value
	if (!GetExpressionEx("@cr0", &qwCR0, NULL)) {
		dprintf("[-] Error evaluating MASM expression!\n");
		goto cleanup;
	}

	// Check if Paging is enabled
	if (!_bittest64((const LONG64*)&qwCR0, 31)) {
		dprintf("[-] Paging is disabled!\n");
		goto cleanup;
	}

	// Read CR4 value
	if (!GetExpressionEx("@cr4", &qwCR4, NULL)) {
		dprintf("[-] Error evaluating MASM expression!\n");
		goto cleanup;
	}

	// Check if Physical Address Extension (PAE) is enabled
	if (!_bittest64((const LONG64*)&qwCR4, 5)) {
		dprintf("[-] Physical Address Extension (PAE) is disabled!\n");
		goto cleanup;
	}

	// Read IA32_EFER (Extended Feature Enables) MSR
	ReadMsr(0xC0000080, &qwIa32Efer);

	// Check if IA-32e mode operation (IA32_EFER.LME) is enabled
	if (!_bittest64((const LONG64*)&qwIa32Efer, 8)) {
		dprintf("[-] IA-32e mode operation (IA32_EFER.LME) is disabled!\n");
		goto cleanup;
	}

	// Check if 57-bit linear addresses are disabled
	if (_bittest64((const LONG64*)&qwCR4, 12)) {
		dprintf("[-] 5-level IA-32e paging mode is enabled!\n");
		goto cleanup;
	}

	dprintf("[+] 4-level IA-32e paging mode is enabled!\n");
	bFlag = TRUE;

	// Cleanup
cleanup:
	return bFlag;
}

_Use_decl_annotations_
VOID __stdcall get_pml4_autoentry_index(
	HANDLE hCurrentProcess,
	HANDLE hCurrentThread,
	QWORD  qwCurrentPc,
	DWORD  dwProcessor,
	PCSTR  strArgs
) {
	// Init local variables
	QWORD qwCR3 = 0;
	QWORD qwPML4BasePa = 0;
	DWORD dwPML4Index = 0;
	PML4E pml4e; ZERO_MEMORY(&pml4e, sizeof(PML4E));
	DWORD dwBytesRead = 0;
	DWORD dwPML4AutoEntryIndex = 0;

	// Determine if the target uses 64-bit pointers
	if (!IsPtr64()) {
		dprintf("[-] IA-32 target is not supported by this extension!\n");
		goto cleanup;
	}

	// Check if paging mode == 4-level IA-32e
	// Add a check for HLAT paging (IA32_VMX_PROCBASED_CTLS3[1] - Enable HLAT)
	if (!check_4_level_paging_mode(hCurrentProcess, hCurrentThread, qwCurrentPc, dwProcessor, strArgs)) {
		goto cleanup;
	}

	// Convert string representation of CR3 value to an integer
	if (!StrToInt64ExA(strArgs, STIF_SUPPORT_HEX, (LONGLONG*)&qwCR3)) {
		dprintf("[-] Invalid args!\n");
		goto cleanup;
	}
	dprintf("[*] CR3=0x%I64X\n", qwCR3);

	// CR3 contains the physical address of the first paging structure that the processor will use for linear address translation
	// In 4-level IA-32e paging mode, the first paging structure is the Page Map Level 4 (PML4) table
	// In 4-level IA-32e paging mode, physical address width == MAXPHYADDR (given by CPUID.80000008H:EAX[7:0], MAXPHYADDR is at most 52)
	// In Windows x64, MAXPHYADDR == 48
	// CR3[MAXPHYADDR–1:12] == Physical address of the 4-KByte aligned PML4 table used for linear-address translation
	qwPML4BasePa = PFN_TO_PAGE(extract_bits(qwCR3, 12, 36), PAGE_SIZE_4KB);
	dprintf("[+] Page Map Level 4 (PML4) table base PA=0x%I64X\n", qwPML4BasePa);

	// A PML4 table comprises 512 64-bit entries (PML4Es)
	// A PML4E is identified using a PML4 index == VA[47:39] (9 bits)
	// Each PML4E controls access to a 512 GB region of the linear-address space
	// In Windows x64, the lower 256 PML4Es are used to map the UVAS while the higher 256 PML4Es are used to map the KVAS
	// Every valid PML4E contains a PFN (PA >> PAGE_SHIFT) which usually reference another paging structure (base of the next paging structure)
	// In Windows x64, a single PML4E in the upper range of every PML4 table is set up in a special way such that its PFN points to the base of the PML4 table itself
	// This special PML4E is called the self-reference entry/auto-entry
	// This special PML4E maps a 512 GB region in KVAS called the PTE Space that contains the 4-level paging structure pages for user mode and kernel mode virtual address space mappings
	// This way the Memory Manager can access by KVA any paging structure entry (PxE) for any VA via self-map
	// Starting from 64-bit Windows 10 1607 Anniversary Update (RS1) Build 14393, the index for this entry is randomized at boot time as part of KASLR (earlier, index fixed at 0x1ED)
	// The PML4 table auto-entry index is maintained by the NT Kernel, so bit 47 must be set for this index (canonical addressing)
	for (dwPML4Index = 0x100; dwPML4Index < 0x200; dwPML4Index++) {
		ReadPhysical((qwPML4BasePa + (dwPML4Index * sizeof(PML4E))), &pml4e.Value, sizeof(PML4E), &dwBytesRead);
		if (dwBytesRead != sizeof(PML4E)) {
			dprintf("[-] Error reading physical memory!\n");
			goto cleanup;
		}

		// Check for invalid PML4E (an entry that is used neither to reference another paging structure nor to map a page)
		if (pml4e.P == 0 || pml4e.PS == 1 || pml4e.Reserved1 != 0) {
			continue;
		}

		// Check for self-reference entry
		if (PFN_TO_PAGE(pml4e.PFN, PAGE_SIZE_4KB) == qwPML4BasePa) {
			dwPML4AutoEntryIndex = dwPML4Index;
			dprintf("[+] PML4 auto-entry found at index: 0x%X (0n%d)\n", dwPML4AutoEntryIndex, dwPML4AutoEntryIndex);
			break;
		}
	}

	// Cleanup
cleanup:
	return;
}

_Use_decl_annotations_
VOID __stdcall get_pxe_base(
	HANDLE hCurrentProcess,
	HANDLE hCurrentThread,
	QWORD  qwCurrentPc,
	DWORD  dwProcessor,
	PCSTR  strArgs
) {
	// Init local variables
	DWORD dwPML4AutoEntryIndex = 0;
	VIRTUAL_ADDRESS virtualAddress; ZERO_MEMORY(&virtualAddress, sizeof(VIRTUAL_ADDRESS));
	QWORD qwPTEBaseKva = 0;
	QWORD qwPDEBaseKva = 0;
	QWORD qwPDPTEBaseKva = 0;
	QWORD qwPML4EBaseKva = 0;

	// Determine if the target uses 64-bit pointers
	if (!IsPtr64()) {
		dprintf("[-] IA-32 target is not supported by this extension!\n");
		goto cleanup;
	}

	// Check if paging mode == 4-level IA-32e
	// Add a check for HLAT paging (IA32_VMX_PROCBASED_CTLS3[1] - Enable HLAT)
	if (!check_4_level_paging_mode(hCurrentProcess, hCurrentThread, qwCurrentPc, dwProcessor, strArgs)) {
		goto cleanup;
	}

	// Convert string representation of the PML4 table auto-entry index to an integer
	if (!StrToIntExA(strArgs, STIF_SUPPORT_HEX, (int*)&dwPML4AutoEntryIndex)) {
		dprintf("[-] Invalid args!\n");
		goto cleanup;
	}
	dprintf("[*] PML4 table auto-entry index: 0x%X (0n%d)\n", dwPML4AutoEntryIndex, dwPML4AutoEntryIndex);

	// Compute PTE range starting address (first PTE)
	virtualAddress.Unused = 0xFFFF; // canonical addressing
	virtualAddress.PML4Index = dwPML4AutoEntryIndex;
	virtualAddress.PDPTIndex = 0x000;
	virtualAddress.PDIndex = 0x000;
	virtualAddress.PTIndex = 0x000;
	virtualAddress.Offset4KB = 0x000;
	qwPTEBaseKva = virtualAddress.Value;
	dprintf("[+] PTE_BASE=0x%I64X\n", qwPTEBaseKva);

	// Compute PDE range starting address (first PDE)
	virtualAddress.Unused = 0xFFFF; // canonical addressing
	virtualAddress.PML4Index = dwPML4AutoEntryIndex;
	virtualAddress.PDPTIndex = dwPML4AutoEntryIndex;
	virtualAddress.PDIndex = 0x000;
	virtualAddress.PTIndex = 0x000;
	virtualAddress.Offset4KB = 0x000;
	qwPDEBaseKva = virtualAddress.Value;
	dprintf("[+] PDE_BASE=0x%I64X\n", qwPDEBaseKva);

	// Compute PDPTE range starting address (first PDPTE)
	virtualAddress.Unused = 0xFFFF; // canonical addressing
	virtualAddress.PML4Index = dwPML4AutoEntryIndex;
	virtualAddress.PDPTIndex = dwPML4AutoEntryIndex;
	virtualAddress.PDIndex = dwPML4AutoEntryIndex;
	virtualAddress.PTIndex = 0x000;
	virtualAddress.Offset4KB = 0x000;
	qwPDPTEBaseKva = virtualAddress.Value;
	dprintf("[+] PPE_BASE=0x%I64X\n", qwPDPTEBaseKva);

	// Compute PML4E range starting address (first PML4E)
	virtualAddress.Unused = 0xFFFF; // canonical addressing
	virtualAddress.PML4Index = dwPML4AutoEntryIndex;
	virtualAddress.PDPTIndex = dwPML4AutoEntryIndex;
	virtualAddress.PDIndex = dwPML4AutoEntryIndex;
	virtualAddress.PTIndex = dwPML4AutoEntryIndex;
	virtualAddress.Offset4KB = 0x000;
	qwPML4EBaseKva = virtualAddress.Value;
	dprintf("[+] PXE_BASE=0x%I64X\n", qwPML4EBaseKva);

	dprintf("[+] PXE_SELFMAP=0x%I64X\n", (qwPML4EBaseKva + (dwPML4AutoEntryIndex * 0x08ULL)));
	dprintf("[+] PXE_TOP=0x%I64X\n", (qwPML4EBaseKva + 0x1000 - 0x01));
	dprintf("[+] PPE_TOP=0x%I64X\n", (qwPDPTEBaseKva + (0x1000ULL * 0x200) - 0x01));
	dprintf("[+] PDE_TOP=0x%I64X\n", (qwPDEBaseKva + (0x1000ULL * 0x200 * 0x200) - 0x01));
	dprintf("[+] PTE_TOP=0x%I64X\n", (qwPTEBaseKva + (0x1000ULL * 0x200 * 0x200 * 0x200) - 0x01));

	// Cleanup
cleanup:
	return;
}

_Use_decl_annotations_
VOID __stdcall get_pxe_address(
	HANDLE hCurrentProcess,
	HANDLE hCurrentThread,
	QWORD  qwCurrentPc,
	DWORD  dwProcessor,
	PCSTR  strArgs
) {
	// Init local variables
	QWORD qwVirtualAddress = 0;
	DWORD dwPML4AutoEntryIndex = 0;
	VIRTUAL_ADDRESS virtualAddress; ZERO_MEMORY(&virtualAddress, sizeof(VIRTUAL_ADDRESS));
	QWORD qwPTEKva = 0;
	QWORD qwPDEKva = 0;
	QWORD qwPDPTEKva = 0;
	QWORD qwPML4EKva = 0;

	// Determine if the target uses 64-bit pointers
	if (!IsPtr64()) {
		dprintf("[-] IA-32 target is not supported by this extension!\n");
		goto cleanup;
	}

	// Check if paging mode == 4-level IA-32e
	// Add a check for HLAT paging (IA32_VMX_PROCBASED_CTLS3[1] - Enable HLAT)
	if (!check_4_level_paging_mode(hCurrentProcess, hCurrentThread, qwCurrentPc, dwProcessor, strArgs)) {
		goto cleanup;
	}

	// Convert string representation of the VA to an integer
	if (!StrToInt64ExA(strArgs, STIF_SUPPORT_HEX, (LONGLONG*)&qwVirtualAddress)) {
		dprintf("[-] Invalid args!\n");
		goto cleanup;
	}
	dprintf("[*] VA=0x%I64X\n", qwVirtualAddress);

	// Convert string representation of the PML4 table auto-entry index to an integer
	if (!StrToIntExA(StrStrA(strArgs, " "), STIF_SUPPORT_HEX, (int*)&dwPML4AutoEntryIndex)) {
		dprintf("[-] Invalid args!\n");
		goto cleanup;
	}
	dprintf("[*] PML4 table auto-entry index: 0x%X (0n%d)\n", dwPML4AutoEntryIndex, dwPML4AutoEntryIndex);

	// Compute PTE KVA for the given VA
	// Step 1: Shift the VA 9 bits to the right (shift by 1 paging structure index slot)
	// Step 2: Clear the lower 3 bits of the VA (physical page offset is now acting as PT index)
	// Step 3: Replace the PML4 table index of the VA with the PML4 table auto-entry index (PML4 table is referenced twice)
	// Step 4: Set the upper 16 bits of the VA to 1 (canonical address)
	// The PML4 table index selects an entry from the PML4 table that references itself
	// The PDPT index (now original PML4 table index) selects an entry from the PML4 table for the given VA
	// The PD table index (now original PDPT index) selects an entry from the PDPT for the given VA
	// The PT index (now original PD table index) selects an entry from the PD table (PT which maps the given VA is mapped as the physical page)
	// The physical page offset (now original PT index) gives the PA of the PTE that maps the given VA
	// Note: Whether this PxE maps the given VA depends on the page size
	virtualAddress.Value = clear_lower_bits(__ull_rshift(qwVirtualAddress, 9), 3);
	virtualAddress.PML4Index = dwPML4AutoEntryIndex;
	virtualAddress.Unused = 0xFFFF;
	qwPTEKva = virtualAddress.Value;
	dprintf("[+] PTE KVA=0x%I64X\n", qwPTEKva);

	// Compute PDE KVA for the given VA
	virtualAddress.Value = clear_lower_bits(__ull_rshift(qwVirtualAddress, 18), 3);
	virtualAddress.PML4Index = dwPML4AutoEntryIndex;
	virtualAddress.PDPTIndex = dwPML4AutoEntryIndex;
	virtualAddress.Unused = 0xFFFF;
	qwPDEKva = virtualAddress.Value;
	dprintf("[+] PDE KVA=0x%I64X\n", qwPDEKva);

	// Compute PDPTE KVA for the given VA
	virtualAddress.Value = clear_lower_bits(__ull_rshift(qwVirtualAddress, 27), 3);
	virtualAddress.PML4Index = dwPML4AutoEntryIndex;
	virtualAddress.PDPTIndex = dwPML4AutoEntryIndex;
	virtualAddress.PDIndex = dwPML4AutoEntryIndex;
	virtualAddress.Unused = 0xFFFF;
	qwPDPTEKva = virtualAddress.Value;
	dprintf("[+] PPE KVA=0x%I64X\n", qwPDPTEKva);

	// Compute PML4E KVA for the given VA
	virtualAddress.Value = clear_lower_bits(__ull_rshift(qwVirtualAddress, 36), 3);
	virtualAddress.PML4Index = dwPML4AutoEntryIndex;
	virtualAddress.PDPTIndex = dwPML4AutoEntryIndex;
	virtualAddress.PDIndex = dwPML4AutoEntryIndex;
	virtualAddress.PTIndex = dwPML4AutoEntryIndex;
	virtualAddress.Unused = 0xFFFF;
	qwPML4EKva = virtualAddress.Value;
	dprintf("[+] PXE KVA=0x%I64X\n", qwPML4EKva);

	// Cleanup
cleanup:
	return;
}

#pragma endregion