// ========================================================================
// File: DrvMain.cpp
//
// Author: winterknife
//
// Description: Source file that contains the SYS entry point
//
// Modifications:
//  2026-04-13	Created
//  2026-05-05  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/Common.h"
#include "../Inc/KernelToUserInjection.h"

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

/// @brief DRIVER_UNLOAD callback routine that gets called to uninitialize the driver when it is unloaded
/// @param pDriverObject Pointer to DRIVER_OBJECT structure representing the driver's driver object
_IRQL_requires_(PASSIVE_LEVEL)
EXTERN_C __declspec(code_seg("PAGE")) VOID __stdcall driver_unload(
	_In_ PDRIVER_OBJECT pDriverObject
) {
	// Suppress W4 warning - C4100
	UNREFERENCED_PARAMETER(pDriverObject);

	DEBUG_PRINT("--- %s.sys Unloaded ---\n", __MODULE__);
}

/// @brief DRIVER_INITIALIZE callback routine that gets called to initialize the driver when it is loaded
/// @param pDriverObject Pointer to DRIVER_OBJECT structure representing the driver's driver object
/// @param puncRegistryPath Pointer to UNICODE_STRING structure specifying the path to the driver's registry key
/// @return STATUS_SUCCESS or an appropriate error status
_Success_(return >= 0) _Must_inspect_result_ _IRQL_requires_(PASSIVE_LEVEL)
EXTERN_C __declspec(code_seg("INIT")) NTSTATUS __stdcall DriverEntry(
	_In_ PDRIVER_OBJECT  pDriverObject,
	_In_ PUNICODE_STRING puncRegistryPath
) {
	DEBUG_PRINT("+++ %s.sys Loaded +++\n", __MODULE__);
	DEBUG_PRINT("%s.sys Built %s %s\n", __MODULE__, __DATE__, __TIME__);
	DEBUG_PRINT("%s: DriverObject = %p\n", __MODULE__, pDriverObject);
	DEBUG_PRINT("%s: RegistryPath = %wZ\n", __MODULE__, puncRegistryPath);

	// Set routine to be called on driver unload
	pDriverObject->DriverUnload = static_cast<PDRIVER_UNLOAD>(driver_unload);

	// Inject ring 3 shellcode to a user-land process
	BYTE byarrPayload[] = { 0xCC, 0x90, 0xC3 }; // int3; nop; ret;
	inject_payload(L"winlogon.exe", byarrPayload, sizeof(byarrPayload));

	return STATUS_SUCCESS;
}

#pragma endregion