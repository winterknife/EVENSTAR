// ========================================================================
// File: ReadInterruptDescriptorTable.cpp
//
// Author: winterknife
//
// Description: Source file that contains the necessary routines to read and
// parse all the gate descriptors in the Interrupt Descriptor Table (IDT)
//
// Modifications:
//  2025-06-23	Created
//  2025-06-29  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/ReadInterruptDescriptorTable.h"
#include "../Inc/DbgExt.h"
#include <Shlwapi.h>

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
		"Help for debugger extension DLL ReadIDTDbgExt.dll\n"
		"   help     - Show help menu\n"
		"   read_idt - Read and parse the gate descriptors in the Interrupt Descriptor Table (IDT)\n"
	);
}

_Use_decl_annotations_
VOID __stdcall read_idt(
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

	// Reload symbols
	ReloadSymbols(NULL);

	dprintf("[!] Current processor number = %d\n", dwProcessor);

	// Init local variables
	QWORD qwIdtBaseKva = 0;
	QWORD qwIdtLimit = 0;
	QWORD qwKpcrKva = 0;
	QWORD qwKprcbKva = 0;
	DWORD dwKinterruptTableBaseOffset = 0;
	QWORD qwKinterruptTableBaseKva = 0;
	DWORD dwIndex = 0;
	INTERRUPT_TRAP_GATE_DESCRIPTOR interruptTrapGateDescriptor; ZERO_MEMORY(&interruptTrapGateDescriptor, sizeof(INTERRUPT_TRAP_GATE_DESCRIPTOR));
	QWORD qwInterruptHandlerKva = 0;
	QWORD qwKinterruptKva = 0;
	CHAR charrSymbolName[MAX_PATH]; ZERO_MEMORY(&charrSymbolName, sizeof(charrSymbolName));
	DWORD_PTR dwptrDisplacement = 0;
	CHAR charrBuffer[MAX_PATH]; ZERO_MEMORY(&charrBuffer, sizeof(charrBuffer));

	// Determine if the target uses 64-bit pointers
	if (!IsPtr64()) {
		dprintf("[-] IA-32 target is not supported by this extension!\n");
		goto cleanup;
	}

	// Read IDT Base Address
	if (!GetExpressionEx("@idtr", &qwIdtBaseKva, NULL)) {
		dprintf("[-] Error evaluating MASM expression!\n");
		goto cleanup;
	}
	dprintf("[+] IDT Base Address=0x%I64X\n", qwIdtBaseKva);

	// Read IDT Limit
	if (!GetExpressionEx("@idtl", &qwIdtLimit, NULL)) {
		dprintf("[-] Error evaluating MASM expression!\n");
		goto cleanup;
	}
	dprintf("[+] IDT Limit=0x%X\n", qwIdtLimit);

	// Get Kernel Processor Control Region (KPCR) KVA
	if (!GetExpressionEx("@$pcr", &qwKpcrKva, NULL)) {
		dprintf("[-] Error evaluating MASM expression!\n");
		goto cleanup;
	}
	dprintf("[+] nt!_KPCR KVA=0x%I64X\n", qwKpcrKva);

	// Get Kernel Processor Control Block (KPRCB) KVA
	if (!ReadPointer((qwKpcrKva + 0x20), &qwKprcbKva)) {
		dprintf("[-] Error reading pointer!\n");
		goto cleanup;
	}
	dprintf("[+] nt!_KPRCB KVA=0x%I64X\n", qwKprcbKva);

	// Get interrupt object table base offset
	// WinDbg command: dt nt!_KPRCB InterruptObject
	if (GetFieldOffset("nt!_KPRCB", "InterruptObject", &dwKinterruptTableBaseOffset)) {
		dprintf("[-] Error getting structure offset!\n");
		goto cleanup;
	}

	// Get interrupt object table base KVA
	qwKinterruptTableBaseKva = qwKprcbKva + dwKinterruptTableBaseOffset;
	dprintf("[+] nt!_KPRCB.InterruptObject[0] KVA=0x%I64X\n", qwKinterruptTableBaseKva);

	// The Interrupt Descriptor Table (IDT) associates each exception or interrupt vector with a gate descriptor for the procedure used to service the associated exception or interrupt
	// The IDT is an array of 16-byte descriptors (in IA-32e mode)
	// There are only 256 interrupt or exception vectors so the IDT should contain a maximum of 256 descriptors
	// The IDT lies in the KVAS
	// In IA-32e mode, there can be two types of entries in the IDT: interrupt gate descriptor and trap gate descriptor
	// When an exception/interrupt is handled through an interrupt gate, the EFLAGS.IF flag is automatically cleared, which disables maskable hardware interrupts
	// If an exception/interrupt is handled through a trap gate, the EFLAGS.IF flag is not cleared
	// Vector numbers in the range 0 through 31 are reserved by the Intel 64 and IA-32 architectures for architecture-defined exceptions and interrupts
	// Vector numbers in the range 32 to 255 are designated as user-defined interrupts and are not reserved by the Intel 64 and IA-32 architecture
	for (dwIndex = 0; dwIndex < 256; dwIndex++) {
		if (!ReadMemory((qwIdtBaseKva + (dwIndex * sizeof(INTERRUPT_TRAP_GATE_DESCRIPTOR))), &interruptTrapGateDescriptor, sizeof(INTERRUPT_TRAP_GATE_DESCRIPTOR), NULL)) {
			dprintf("[-] Error reading virtual memory!\n");
			goto cleanup;
		}

		// Check for empty descriptor slots
		// All empty descriptor slots in the IDT should have the present flag for the descriptor set to 0
		if (interruptTrapGateDescriptor.P == 0) {
			continue;
		}

		// Get the address of the entry point of the Interrupt Service Routine (ISR)
		qwInterruptHandlerKva = __ll_lshift(interruptTrapGateDescriptor.OffsetHigh, 32) + __ll_lshift(interruptTrapGateDescriptor.OffsetMiddle, 16) + interruptTrapGateDescriptor.OffsetLow;
		
		// Get the interrupt object corresponding to the interrupt vector from the array of interrupt object pointers
		if (!ReadPointer((qwKinterruptTableBaseKva + (dwIndex * sizeof(PVOID))), &qwKinterruptKva)) {
			dprintf("[-] Error reading pointer!\n");
			goto cleanup;
		}
		
		// Get the ISR KVA from the interrupt object
		if (qwKinterruptKva) {
			if (!ReadPointer((qwKinterruptKva + 0x20), &qwInterruptHandlerKva)) {
				dprintf("[-] Error reading pointer!\n");
				goto cleanup;
			}

			if (!qwInterruptHandlerKva) {
				if (!ReadPointer((qwKinterruptKva + 0x18), &qwInterruptHandlerKva)) {
					dprintf("[-] Error reading pointer!\n");
					goto cleanup;
				}
			}
		}

		// Get the symbol name
		GetSymbol(qwInterruptHandlerKva, charrSymbolName, &dwptrDisplacement);
		wnsprintfA(charrBuffer, MAX_PATH, "%s+0x%X", charrSymbolName, (WORD)dwptrDisplacement);

		// Display IDT gate descriptor
		dprintf("----------------------------------------------------------------------\n");

		dprintf("[+] Vector Number: 0x%X (0n%d)\n", dwIndex, dwIndex);

		if (interruptTrapGateDescriptor.Type == 14)
			dprintf("[+] Type: Interrupt Gate\n");
		else if (interruptTrapGateDescriptor.Type == 15)
			dprintf("[+] Type: Trap Gate\n");

		dprintf("[+] Segment Selector=0x%X\n", interruptTrapGateDescriptor.SegmentSelector);

		if (dwptrDisplacement)
			dprintf("[+] ISR KVA=0x%I64X (%s)\n", qwInterruptHandlerKva, charrBuffer);
		else
			dprintf("[+] ISR KVA=0x%I64X (%s)\n", qwInterruptHandlerKva, charrSymbolName);

		if (interruptTrapGateDescriptor.IST)
			dprintf("[+] IST=0x%X\n", interruptTrapGateDescriptor.IST);

		dprintf("[+] DPL=0x%X\n", interruptTrapGateDescriptor.DPL);

		dprintf("----------------------------------------------------------------------\n");
	}
	
	// Cleanup
cleanup:
	return;
}

#pragma endregion