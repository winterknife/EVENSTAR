// ========================================================================
// File: GetCurrentProcessorNumber.cpp
//
// Author: winterknife
//
// Description: Source file that contains the necessary routines to retrieve
// the current logical processor ID
//
// Modifications:
//  2025-07-01	Created
//  2025-07-07  Updated
// ========================================================================

// ========================================================================
// Includes
// ========================================================================

#include "../Inc/GetCurrentProcessorNumber.h"

// ========================================================================
// Routines
// ========================================================================

#pragma region ROUTINES

_Use_decl_annotations_
DWORD __stdcall get_current_processor_number(
	VOID
) {
	// Init local variables
	CPUID_REGISTERS cpuidRegisters; ZERO_MEMORY(&cpuidRegisters, sizeof(CPUID_REGISTERS));
    DWORD dwIa32TscAux = 0;
    DWORD dwSegmentLimit = 0;
    QWORD qwRflags = 0;

    // Check if processor supports the RDPID instruction for reading the IA32_TSC_AUX MSR value
    // RDPID instruction support is only available since Sunny Cove Intel microarchitecture (2019)
    __cpuidex((int*)&cpuidRegisters, 0x07, 0x00);
    if (_bittest((const LONG*)&cpuidRegisters.dwECX, 22)) {
        return _rdpid_u32(); // RDPID — Read Processor ID
    }
    else {
        // Check if processor supports the RDTSCP instruction and the IA32_TSC_AUX MSR
        // RDTSCP and IA32_TSC_AUX support are only available since Nehalem Intel microarchitecture (2008)
        __cpuidex((int*)&cpuidRegisters, 0x80000001, 0x00);
        if (_bittest((const LONG*)&cpuidRegisters.dwEDX, 27)) {
            __rdtscp((unsigned int*)&dwIa32TscAux); // RDTSCP — Read Time-Stamp Counter and Processor ID
            return dwIa32TscAux;
        }
        else {
            // Get the segment limit of the 32-bit TEB segment
            dwSegmentLimit = __segmentlimit(KGDT_R3_TEB | RPL_MASK); // LSL — Load Segment Limit

            // Check if EFLAGS.ZF is set
            // If the segment descriptor cannot be accessed or is an invalid type for the instruction, the EFLAGS.ZF flag is cleared
            qwRflags = __readeflags(); // PUSHF/PUSHFD/PUSHFQ — Push EFLAGS Register Onto the Stack
            if (_bittest64((const LONG64*)&qwRflags, 6)) {
                // Read the processor ID from the segment limit
                // In Windows, the segment limit of the segment descriptor selected by the TEB selector contains the current logical processor's ID in bits 14 to 19
                return (dwSegmentLimit >> 0xE);
            }
            else {
                return 0xFFFFFFFFUL;
            }
        }
    }
}

#pragma endregion