// ========================================================================
// File: KernelToUserInjection.h
//
// Author: winterknife
//
// Description: Header file for KernelToUserInjection.cpp source file
//
// Modifications:
//  2026-04-13	Created
//  2026-04-20  Updated
// ========================================================================

// ========================================================================
// Pragmas
// ========================================================================

#pragma once

// ========================================================================
// Includes
// ========================================================================

#include "Common.h"

// ========================================================================
// Macros
// ========================================================================

#pragma region MACROS

#define SystemProcessInformation 0x05UL

#pragma endregion

// ========================================================================
// Structures/Enumerations/Unions
// ========================================================================

#pragma region STRUCTS_ENUMS_UNIONS

// nt!_KTHREAD_STATE enum definition
typedef enum _KTHREAD_STATE {
    Initialized,
    Ready,
    Running,
    Standby,
    Terminated,
    Waiting,
    Transition,
    DeferredReady,
    GateWaitObsolete,
    WaitingForProcessInSwap,
    MaximumThreadState
} KTHREAD_STATE, *PKTHREAD_STATE;

// nt!_SYSTEM_THREAD_INFORMATION structure definition
typedef struct _SYSTEM_THREAD_INFORMATION {
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER CreateTime;
    ULONG WaitTime;
    PVOID StartAddress;
    CLIENT_ID ClientId;
    KPRIORITY Priority;
    KPRIORITY BasePriority;
    ULONG ContextSwitches;
    KTHREAD_STATE ThreadState;
    KWAIT_REASON WaitReason;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

// nt!_SYSTEM_PROCESS_INFORMATION structure definition
typedef struct _SYSTEM_PROCESS_INFORMATION {
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    LARGE_INTEGER WorkingSetPrivateSize; // since VISTA
    ULONG HardFaultCount; // since WIN7
    ULONG NumberOfThreadsHighWatermark; // since WIN7
    ULONGLONG CycleTime; // since WIN7
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ImageName;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    HANDLE InheritedFromUniqueProcessId;
    ULONG HandleCount;
    ULONG SessionId;
    ULONG_PTR UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    LARGE_INTEGER ReadOperationCount;
    LARGE_INTEGER WriteOperationCount;
    LARGE_INTEGER OtherOperationCount;
    LARGE_INTEGER ReadTransferCount;
    LARGE_INTEGER WriteTransferCount;
    LARGE_INTEGER OtherTransferCount;
    SYSTEM_THREAD_INFORMATION Threads[1]; // SystemProcessInformation
    // SYSTEM_EXTENDED_THREAD_INFORMATION Threads[1]; // SystemExtendedProcessinformation
    // SYSTEM_EXTENDED_THREAD_INFORMATION + SYSTEM_PROCESS_INFORMATION_EXTENSION // SystemFullProcessInformation
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

// nt!_KAPC_ENVIRONMENT structure definition
typedef enum _KAPC_ENVIRONMENT {
    OriginalApcEnvironment,
    AttachedApcEnvironment,
    CurrentApcEnvironment,
    InsertApcEnvironment
} KAPC_ENVIRONMENT, *PKAPC_ENVIRONMENT;

#pragma endregion

// ========================================================================
// Undocumented kernel API function prototypes
// ========================================================================

#pragma region PROTOTYPES

EXTERN_C NTSYSAPI NTSTATUS NTAPI ZwQuerySystemInformation(
    _In_                                            ULONG  SystemInformationClass,
    _Out_writes_bytes_opt_(SystemInformationLength) PVOID  SystemInformation,
    _In_                                            ULONG  SystemInformationLength,
    _Out_opt_                                       PULONG ReturnLength
);

typedef _Function_class_(KNORMAL_ROUTINE) _IRQL_requires_(PASSIVE_LEVEL) _IRQL_requires_same_ VOID NTAPI KNORMAL_ROUTINE(
    _In_opt_ PVOID NormalContext,
    _In_opt_ PVOID SystemArgument1,
    _In_opt_ PVOID SystemArgument2
);
typedef KNORMAL_ROUTINE* PKNORMAL_ROUTINE;

typedef _Function_class_(KKERNEL_ROUTINE) _IRQL_requires_(APC_LEVEL) _IRQL_requires_same_ VOID NTAPI KKERNEL_ROUTINE(
    _In_                          PRKAPC            Apc,
    _Inout_ _Deref_pre_maybenull_ PKNORMAL_ROUTINE* NormalRoutine,
    _Inout_ _Deref_pre_maybenull_ PVOID*            NormalContext,
    _Inout_ _Deref_pre_maybenull_ PVOID*            SystemArgument1,
    _Inout_ _Deref_pre_maybenull_ PVOID*            SystemArgument2
);
typedef KKERNEL_ROUTINE* PKKERNEL_ROUTINE;

typedef _Function_class_(KRUNDOWN_ROUTINE) _IRQL_requires_(PASSIVE_LEVEL) _IRQL_requires_same_ VOID NTAPI KRUNDOWN_ROUTINE(
    _In_ PRKAPC Apc
);
typedef KRUNDOWN_ROUTINE* PKRUNDOWN_ROUTINE;

EXTERN_C NTKERNELAPI VOID NTAPI KeInitializeApc(
    _Out_    PRKAPC            Apc,
    _In_     PRKTHREAD         Thread,
    _In_     KAPC_ENVIRONMENT  Environment,
    _In_     PKKERNEL_ROUTINE  KernelRoutine,
    _In_opt_ PKRUNDOWN_ROUTINE RundownRoutine,
    _In_opt_ PKNORMAL_ROUTINE  NormalRoutine,
    _In_     KPROCESSOR_MODE   Mode,
    _In_opt_ PVOID             NormalContext
);

EXTERN_C NTKERNELAPI BOOLEAN NTAPI KeInsertQueueApc(
    _Inout_  PRKAPC    Apc,
    _In_opt_ PVOID     SystemArgument1,
    _In_opt_ PVOID     SystemArgument2,
    _In_     KPRIORITY Increment
);

#pragma endregion

// ========================================================================
// C routine declarations
// ========================================================================

#pragma region DECLARATIONS

/// @brief Find the Process ID (PID) of a process given its name and the first Thread ID (TID) of a thread in the process that is in an alertable wait state
/// @param puncImageName Pointer to the UNICODE_STRING structure that contains the image name of the target process
/// @param pdwPid Pointer to a DWORD that will receive the PID of the target process, returns 0 if the routine fails
/// @param pdwTid Pointer to a DWORD that will receive the TID of a thread in an alertable wait state, returns 0 if the routine fails
/// @return STATUS_SUCCESS or an appropriate error status
_Success_(return >= 0) _Must_inspect_result_ _IRQL_requires_(PASSIVE_LEVEL)
EXTERN_C DECLSPEC_NOINLINE NTSTATUS __stdcall query_process_by_name(
	_In_            PUNICODE_STRING puncImageName,
    _Always_(_Out_) PDWORD          pdwPid,
    _Always_(_Out_) PDWORD          pdwTid
);

/// @brief Inject a ring 3 payload from ring 0 to a remote process using user-mode APC
/// @param wstrImageName Pointer to a null-terminated wide-character string representing the image name of the target process
/// @param pPayload KVA of the ring 3 payload buffer
/// @param dwptrPayloadSize Size of the ring 3 payload buffer in bytes
/// @return STATUS_SUCCESS or an appropriate error status
_Success_(return >= 0) _Must_inspect_result_ _IRQL_requires_(PASSIVE_LEVEL)
EXTERN_C DECLSPEC_NOINLINE NTSTATUS __stdcall inject_payload(
    _In_z_                             PCWSTR    wstrImageName,
    _In_reads_bytes_(dwptrPayloadSize) PVOID     pPayload,
    _In_                               DWORD_PTR dwptrPayloadSize
);

#pragma endregion