// ========================================================================
// File: KernelToUserInjection.cpp
//
// Author: winterknife
//
// Description: Source file that contains the necessary routines to inject
// code from kernel-mode into a user-land process
//
// Modifications:
//  2026-04-13	Created
//  2026-04-28  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/KernelToUserInjection.h"

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

_Use_decl_annotations_
NTSTATUS __stdcall query_process_thread_by_name(
	PUNICODE_STRING puncImageName,
	PEPROCESS*      ppEprocess,
	PETHREAD*       ppEthread
) {
	// Init local variables
	NTSTATUS status = STATUS_SUCCESS;
	DWORD dwBufferSize = 0;
	PSYSTEM_PROCESS_INFORMATION pSystemProcessInformation = nullptr;
	PSYSTEM_PROCESS_INFORMATION pSystemProcessInformationCurrentEntry = nullptr;
	HANDLE hPid = nullptr;
	DWORD dwIndex = 0;
	HANDLE hTid = nullptr;

	// Sanity check the inputs
	if (puncImageName == nullptr || ppEprocess == nullptr || ppEthread == nullptr) {
		status = STATUS_INVALID_PARAMETER;
		goto cleanup;
	}

	// Initialize args
	*ppEprocess = nullptr;
	*ppEthread = nullptr;

	// Get the size of the buffer
	status = ZwQuerySystemInformation(SystemProcessInformation, nullptr, 0, &dwBufferSize);
	if (status == STATUS_INFO_LENGTH_MISMATCH) {
		dwBufferSize += PAGE_SIZE;
	}
	else {
		DEBUG_PRINT("[-] ZwQuerySystemInformation #1 error: 0x%08X\n", status);
		goto cleanup;
	}
	
	// Allocate the buffer
	pSystemProcessInformation = static_cast<PSYSTEM_PROCESS_INFORMATION>(ExAllocatePoolZero(NonPagedPoolNx, dwBufferSize, __POOLTAG__));
	if (pSystemProcessInformation == nullptr) {
		status = STATUS_INSUFFICIENT_RESOURCES;
		DEBUG_PRINT("[-] ExAllocatePoolZero #1 error: 0x%08X\n", status);
		goto cleanup;
	}

	// Query the list of active processes
	status = ZwQuerySystemInformation(SystemProcessInformation, pSystemProcessInformation, dwBufferSize, nullptr);
	if (!NT_SUCCESS(status)) {
		DEBUG_PRINT("[-] ZwQuerySystemInformation #2 error: 0x%08X\n", status);
		goto cleanup;
	}

	// Iterate through each SYSTEM_PROCESS_INFORMATION structure
	pSystemProcessInformationCurrentEntry = pSystemProcessInformation;
	do {
		// Compare image name of the current process with the image name of the target process
		if (RtlCompareUnicodeString(&pSystemProcessInformationCurrentEntry->ImageName, puncImageName, true) == 0) {
			// Get the PID of the current process
			hPid = pSystemProcessInformationCurrentEntry->UniqueProcessId;
			DEBUG_PRINT("[+] PID of target process: %d\n", HandleToULong(hPid));

			// Get a referenced pointer to the EPROCESS structure of the current process
			status = PsLookupProcessByProcessId(hPid, ppEprocess);
			if (!NT_SUCCESS(status)) {
				DEBUG_PRINT("[-] PsLookupProcessByProcessId error: 0x%08X\n", status);
				break;
			}

			// Iterate through each SYSTEM_THREAD_INFORMATION structure
			for (dwIndex = 0; dwIndex < pSystemProcessInformationCurrentEntry->NumberOfThreads; dwIndex++) {
				// Get the TID of the current thread
				hTid = pSystemProcessInformationCurrentEntry->Threads[dwIndex].ClientId.UniqueThread;

				// Get a referenced pointer to the ETHREAD structure of the current thread
				status = PsLookupThreadByThreadId(hTid, ppEthread);
				if (!NT_SUCCESS(status)) {
					DEBUG_PRINT("[-] PsLookupThreadByThreadId error: 0x%08X\n", status);
					continue;
				}

				// Check if thread is in an alertable wait state
				// Should we also check for the absence of TEB and ActivationContext?
#pragma message("!!! HARDCODED OPAQUE OFFSET FOR WINDOWS 10 / 11 x64 (ALL VERSIONS) !!!")
				if (_bittest(reinterpret_cast<LONG const*>(reinterpret_cast<DWORD_PTR>(*ppEthread) + 0x74ULL), 4)) {
					DEBUG_PRINT("[+] TID of thread in alertable wait state: %d\n", HandleToULong(hTid));
					break;
				}

				// Decrement reference count
				ObDereferenceObject(*ppEthread);
				*ppEthread = nullptr;
			}

			break;
		}

		// Check for loop exit condition
		if (pSystemProcessInformationCurrentEntry->NextEntryOffset == 0)
			break;

		// Get the next entry
		pSystemProcessInformationCurrentEntry = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(reinterpret_cast<PUCHAR>(pSystemProcessInformationCurrentEntry) + pSystemProcessInformationCurrentEntry->NextEntryOffset);
	} while (true);

	// Cleanup
cleanup:
	if (pSystemProcessInformation)
		ExFreePoolWithTag(pSystemProcessInformation, __POOLTAG__);

	return status;
}

_Use_decl_annotations_
VOID __stdcall kernel_routine(
	PRKAPC            Apc,
	PKNORMAL_ROUTINE* NormalRoutine,
	PVOID*            NormalContext,
	PVOID*            SystemArgument1,
	PVOID*            SystemArgument2
) {
	// Suppress W4 warning - C4100
	UNREFERENCED_PARAMETER(NormalRoutine);
	UNREFERENCED_PARAMETER(NormalContext);
	UNREFERENCED_PARAMETER(SystemArgument2);

	// Insert the APC into the queue of the target thread
	if (!KeInsertQueueApc(static_cast<PRKAPC>(*SystemArgument1), nullptr, nullptr, IO_NO_INCREMENT)) {
		DEBUG_PRINT("[-] KeInsertQueueApc #2 error: 0x%08X\n", STATUS_UNSUCCESSFUL);
		ExFreePoolWithTag(*SystemArgument1, __POOLTAG__);
	}
	else {
		DEBUG_PRINT("[+] Queued a regular user-mode APC to the target thread!\n");
	}

	// Free the special kernel APC object
	ExFreePoolWithTag(Apc, __POOLTAG__);
}

_Use_decl_annotations_
NTSTATUS __stdcall inject_payload(
	PCWSTR    wstrImageName,
	PVOID     pPayload,
	DWORD_PTR dwptrPayloadSize
) {
	// Init local variables
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING uncImageName; ZERO_MEMORY(&uncImageName, sizeof(UNICODE_STRING));
	PEPROCESS pEprocess = nullptr;
	PETHREAD pEthread = nullptr;
	KAPC_STATE kapcState; ZERO_MEMORY(&kapcState, sizeof(KAPC_STATE));
	DWORD_PTR dwptrSize = 0;
	PVOID pBuffer = nullptr;
	DWORD dwOldProtection = 0;
	PKAPC pKapcKernel = nullptr;
	PKAPC pKapcUser = nullptr;

	// Sanity check the inputs
	if (wstrImageName == nullptr || pPayload == nullptr || dwptrPayloadSize == 0) {
		status = STATUS_INVALID_PARAMETER;
		goto cleanup;
	}

	// Get a referenced pointer to the EPROCESS structure of the target process and a referenced pointer to the ETHREAD structure of the target thread
	RtlInitUnicodeString(&uncImageName, wstrImageName);
	status = query_process_thread_by_name(&uncImageName, &pEprocess, &pEthread);
	if (!NT_SUCCESS(status) || pEprocess == nullptr || pEthread == nullptr) {
		goto cleanup;
	}

	// Attach the current thread to the address space of the target process
	KeStackAttachProcess(pEprocess, &kapcState);

	// Allocate RW memory in the target process
	// This userland memory is never properly cleaned up on either success or failure paths
	dwptrSize = dwptrPayloadSize;
	status = ZwAllocateVirtualMemory(ZwCurrentProcess(), &pBuffer, 0, &dwptrSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!NT_SUCCESS(status)) {
		DEBUG_PRINT("[-] ZwAllocateVirtualMemory error: 0x%08X\n", status);
		KeUnstackDetachProcess(&kapcState);
		goto cleanup;
	}
	DEBUG_PRINT("[+] Payload buffer UVA: 0x%p\n", pBuffer);

	// Copy ring 3 payload from KVAS to target process UVAS
	// This is quite risky!
	COPY_MEMORY(pBuffer, pPayload, dwptrPayloadSize);

	// Change page protection of the allocated memory to RX
	status = ZwProtectVirtualMemory(ZwCurrentProcess(), &pBuffer, &dwptrSize, PAGE_EXECUTE_READ, &dwOldProtection);
	if (!NT_SUCCESS(status)) {
		DEBUG_PRINT("[-] ZwProtectVirtualMemory error: 0x%08X\n", status);
		KeUnstackDetachProcess(&kapcState);
		goto cleanup;
	}

	// Detach the current thread from the address space of the target process
	KeUnstackDetachProcess(&kapcState);

	// Allocate memory for the KAPC structures
	pKapcKernel = static_cast<PKAPC>(ExAllocatePoolZero(NonPagedPoolNx, sizeof(KAPC), __POOLTAG__));
	if (pKapcKernel == nullptr) {
		status = STATUS_INSUFFICIENT_RESOURCES;
		DEBUG_PRINT("[-] ExAllocatePoolZero #2 error: 0x%08X\n", status);
		goto cleanup;
	}

	pKapcUser = static_cast<PKAPC>(ExAllocatePoolZero(NonPagedPoolNx, sizeof(KAPC), __POOLTAG__));
	if (pKapcUser == nullptr) {
		status = STATUS_INSUFFICIENT_RESOURCES;
		DEBUG_PRINT("[-] ExAllocatePoolZero #3 error: 0x%08X\n", status);
		ExFreePoolWithTag(pKapcKernel, __POOLTAG__);
		goto cleanup;
	}

	// Initialize the special kernel APC
	KeInitializeApc(pKapcKernel, pEthread, OriginalApcEnvironment, kernel_routine, nullptr, nullptr, KernelMode, nullptr);

	// Initialize the regular user-mode APC
	KeInitializeApc(pKapcUser, pEthread, OriginalApcEnvironment, reinterpret_cast<PKKERNEL_ROUTINE>(ExFreePool), nullptr, reinterpret_cast<PKNORMAL_ROUTINE>(pBuffer), UserMode, nullptr);

	// Insert the APC into the queue of the target thread
	if (!KeInsertQueueApc(pKapcKernel, pKapcUser, nullptr, IO_NO_INCREMENT)) {
		status = STATUS_UNSUCCESSFUL;
		DEBUG_PRINT("[-] KeInsertQueueApc #1 error: 0x%08X\n", status);
		ExFreePoolWithTag(pKapcKernel, __POOLTAG__);
		ExFreePoolWithTag(pKapcUser, __POOLTAG__);
		goto cleanup;
	}
	DEBUG_PRINT("[+] Queued a special kernel APC to the target thread!\n");

	// Cleanup
cleanup:
	if (pEthread)
		ObDereferenceObject(pEthread);

	if (pEprocess)
		ObDereferenceObject(pEprocess);

	return status;
}

#pragma endregion