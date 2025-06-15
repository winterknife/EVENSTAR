// ========================================================================
// File: PageTableWalk.h
//
// Author: winterknife
//
// Description: Header file for PageTableWalk.cpp source file
//
// Modifications:
//  2025-05-20	Created
//  2025-06-08  Updated
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

// In 4-level IA-32e paging mode, possible page sizes == 4 KB, 2 MB, 1 GB
#define PAGE_SIZE_4KB 0x1000ULL
#define PAGE_SIZE_2MB 0x200000ULL
#define PAGE_SIZE_1GB 0x40000000ULL

// Predefined page shifts
#define PAGE_SHIFT_4KB 12u // binary_logarithm(PAGE_SIZE_4KB)
#define PAGE_SHIFT_2MB 21u // binary_logarithm(PAGE_SIZE_2MB)
#define PAGE_SHIFT_1GB 30u // binary_logarithm(PAGE_SIZE_1GB)

// Macro to calculate page shift from page size
#define PAGE_SHIFT(page_size) binary_logarithm(page_size)

// Macro to get the starting address of a physical page/frame from its Page Frame Number (PFN) and page size
#define PFN_TO_PAGE(pfn, page_size) __ll_lshift(pfn, PAGE_SHIFT(page_size)) // PFN * PAGE_SIZE

#pragma endregion

// ========================================================================
// Structures/Enumerations/Unions
// ========================================================================

#pragma region STRUCTS_ENUMS_UNIONS

// CPUID structure for using the return data of CPUID in the application
typedef struct _CPUID_REGISTERS {
    DWORD dwEAX;
    DWORD dwEBX;
    DWORD dwECX;
    DWORD dwEDX;
} CPUID_REGISTERS, *PCPUID_REGISTERS;

// Linear address
#pragma warning(push)
#pragma warning(disable: 4201)
typedef union _VIRTUAL_ADDRESS {
    struct {
        QWORD Offset4KB : 12; // 4 KB Physical Page Offset
        QWORD PTIndex   :  9; // Page Table (PT)
        QWORD PDIndex   :  9; // Page Directory (PD)
        QWORD PDPTIndex :  9; // Page Directory Pointer Table (PDPT)
        QWORD PML4Index :  9; // Page Map Level 4 (PML4)
        QWORD Unused    : 16; // Sign Extend
    };
    struct {
        QWORD Offset2MB : 21; // 2 MB Physical Page Offset
        QWORD           : 43;
    };
    struct {
        QWORD Offset1GB : 30; // 1 GB Physical Page Offset
        QWORD           : 34;
    };
    QWORD Value;
} VIRTUAL_ADDRESS, *PVIRTUAL_ADDRESS;
#pragma warning(pop)

// PML4 Entry (PML4E)
#pragma warning(push)
#pragma warning(disable: 4201)
typedef union _PML4E {
    struct {
        QWORD P         :  1; // Present
        QWORD RW        :  1; // Read/Write
        QWORD US        :  1; // User/Supervisor
        QWORD PWT       :  1; // Page-level Write Through
        QWORD PCD       :  1; // Page-level Cache Disable
        QWORD A         :  1; // Accessed
        QWORD Ignored1  :  1; // Ignored
        QWORD PS        :  1; // Reserved (must be 0)
        QWORD Ignored2  :  3; // Ignored
        QWORD R         :  1; // Restart (HLAT paging)
        QWORD PFN       : 36; // Physical address of 4-KByte aligned page-directory-pointer table referenced by this entry
        QWORD Reserved1 :  4; // Reserved (must be 0)
        QWORD Ignored3  : 11; // Ignored
        QWORD XD        :  1; // Execute Disable, reserved (must be 0) if IA32_EFER.NXE = 0
    };
    QWORD Value;
} PML4E, *PPML4E;
#pragma warning(pop)

// PDPT Entry (PDPTE)
#pragma warning(push)
#pragma warning(disable: 4201)
typedef union _PDPTE {
    struct {
        QWORD P         :  1; // Present
        QWORD RW        :  1; // Read/Write
        QWORD US        :  1; // User/Supervisor
        QWORD PWT       :  1; // Page-level Write Through
        QWORD PCD       :  1; // Page-level Cache Disable
        QWORD A         :  1; // Accessed
        QWORD D         :  1; // Dirty
        QWORD PS        :  1; // Page Size (must be set if entry maps a 1 GB page), reserved (must be 0) if processor doesn't support huge pages
        QWORD G         :  1; // Global (if CR4.PGE = 1, determines whether the translation is global, ignored otherwise)
        QWORD Ignored1  :  2; // Ignored
        QWORD R         :  1; // Restart (HLAT paging)
        QWORD PAT       :  1; // Page Attribute Table (PAT)
        QWORD Reserved1 : 17; // Reserved (must be 0)
        QWORD PFN1      : 18; // Physical address of the 1-GByte page referenced by this entry
        QWORD Reserved2 :  4; // Reserved (must be 0)
        QWORD Ignored2  :  7; // Ignored
        QWORD PK        :  4; // Protection Key (if CR4.PKE = 1 or CR4.PKS = 1, this may control the page’s access rights, ignored otherwise)
        QWORD XD        :  1; // Execute Disable, reserved (must be 0) if IA32_EFER.NXE = 0
    };
    struct {
        QWORD           : 12;
        QWORD PFN2      : 36; // Physical address of 4-KByte aligned page directory referenced by this entry
        QWORD           : 16;
    };
    QWORD Value;
} PDPTE, *PPDPTE;
#pragma warning(pop)

// PD Entry (PDE)
#pragma warning(push)
#pragma warning(disable: 4201)
typedef union _PDE {
    struct {
        QWORD P         :  1; // Present
        QWORD RW        :  1; // Read/Write
        QWORD US        :  1; // User/Supervisor
        QWORD PWT       :  1; // Page-level Write Through
        QWORD PCD       :  1; // Page-level Cache Disable
        QWORD A         :  1; // Accessed
        QWORD D         :  1; // Dirty
        QWORD PS        :  1; // Page Size (must be set if entry maps a 2 MB page)
        QWORD G         :  1; // Global (if CR4.PGE = 1, determines whether the translation is global, ignored otherwise)
        QWORD Ignored1  :  2; // Ignored
        QWORD R         :  1; // Restart (HLAT paging)
        QWORD PAT       :  1; // Page Attribute Table (PAT)
        QWORD Reserved1 :  8; // Reserved (must be 0)
        QWORD PFN1      : 27; // Physical address of the 2-MByte page referenced by this entry
        QWORD Reserved2 :  4; // Reserved (must be 0)
        QWORD Ignored2  :  7; // Ignored
        QWORD PK        :  4; // Protection Key (if CR4.PKE = 1 or CR4.PKS = 1, this may control the page’s access rights, ignored otherwise)
        QWORD XD        :  1; // Execute Disable, reserved (must be 0) if IA32_EFER.NXE = 0
    };
    struct {
        QWORD           : 12;
        QWORD PFN2      : 36; // Physical address of 4-KByte aligned page table referenced by this entry
        QWORD           : 16;
    };
    QWORD Value;
} PDE, *PPDE;
#pragma warning(pop)

// PT Entry (PTE)
#pragma warning(push)
#pragma warning(disable: 4201)
typedef union _PTE {
    struct {
        QWORD P         :  1; // Present
        QWORD RW        :  1; // Read/Write
        QWORD US        :  1; // User/Supervisor
        QWORD PWT       :  1; // Page-level Write Through
        QWORD PCD       :  1; // Page-level Cache Disable
        QWORD A         :  1; // Accessed
        QWORD D         :  1; // Dirty
        QWORD PAT       :  1; // Page Attribute Table (PAT)
        QWORD G         :  1; // Global (if CR4.PGE = 1, determines whether the translation is global, ignored otherwise)
        QWORD Ignored1  :  2; // Ignored
        QWORD R         :  1; // Restart (HLAT paging)
        QWORD PFN       : 36; // Physical address of the 4-KByte page referenced by this entry
        QWORD Reserved1 :  4; // Reserved (must be 0)
        QWORD Ignored2  :  7; // Ignored
        QWORD PK        :  4; // Protection Key (if CR4.PKE = 1 or CR4.PKS = 1, this may control the page’s access rights, ignored otherwise)
        QWORD XD        :  1; // Execute Disable, reserved (must be 0) if IA32_EFER.NXE = 0
    };
    QWORD Value;
} PTE, *PPTE;
#pragma warning(pop)

// Windows x64 hardware PxE (MMU's interpretation)
typedef struct _MMPTE_HARDWARE {
    QWORD Valid               :  1; // Present
    QWORD Dirty1              :  1; // Read/Write (cleared together with Dirty bit)
    QWORD Owner               :  1; // User/Supervisor
    QWORD WriteThrough        :  1; // Page-level Write Through
    QWORD CacheDisable        :  1; // Page-level Cache Disable
    QWORD Accessed            :  1; // Accessed
    QWORD Dirty               :  1; // Dirty
    QWORD LargePage           :  1; // Page Attribute Table (PAT) or Page Size (PS)
    QWORD Global              :  1; // Global
    QWORD CopyOnWrite         :  1; // Copy On Write (CoW)
    QWORD Unused              :  1; // Ignored
    QWORD Write               :  1; // Used by the Memory Manager to recognize the page as writable
    QWORD PageFrameNumber     : 36; // Page Frame Number (PFN)
    QWORD ReservedForHardware :  4; // Reserved (must be 0)
    QWORD ReservedForSoftware :  4; // Reserved (must be 0)
    QWORD WsleAge             :  4; // Working Set List Entry (WSLE)
    QWORD WsleProtection      :  3; // Working Set List Entry (WSLE)
    QWORD NoExecute           :  1; // Execute Disable (XD/NX)
} MMPTE_HARDWARE, *PMMPTE_HARDWARE;

#pragma endregion

// ========================================================================
// C routine declarations
// ========================================================================

#pragma region DECLARATIONS

/// @brief Built-in command to check if the logical processor is using 4-level IA-32e paging mode
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments
/// @return Returns TRUE if the logical processor is using 4-level IA-32e paging mode or FALSE otherwise
_Success_(return != 0) _Must_inspect_result_
extern "C" __declspec(dllexport) BOOLEAN __stdcall check_4_level_paging_mode(
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

/// @brief Built-in command to find the self-reference entry/auto-entry index of the Page Map Level 4 (PML4) table from the CR3
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments (CR3 value)
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall get_pml4_autoentry_index(
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

/// @brief Built-in command to compute the starting KVA of the paging structure entry (PxE) range from the PML4 table auto-entry index
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments (PML4 table auto-entry index)
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall get_pxe_base(
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

/// @brief Built-in command to compute the KVA of the paging structure entry (PxE) that maps the specified VA from the PML4 table auto-entry index
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments (VA and PML4 table auto-entry index)
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall get_pxe_address(
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

/// @brief Built-in command to translate the specified linear address (VA) to its mapped physical address (PA) and determine the VA's access rights from the CR3
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments (VA and CR3 value)
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall get_physical_address(
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

#pragma endregion

// ========================================================================
// C inline routines
// ========================================================================

#pragma region INLINES

/// @brief Extract contiguous bits from an unsigned 64-bit integer
/// @param qwValue The unsigned 64-bit integer value
/// @param dwStart The bit offset specifying the starting position
/// @param dwLength The number of bits to be extracted
/// @return Returns the extracted bits
extern "C" __forceinline QWORD __stdcall extract_bits(
    _In_ QWORD qwValue,
    _In_ DWORD dwStart,
    _In_ DWORD dwLength
) {
    // Init local variables
    CPUID_REGISTERS cpuidRegisters; ZERO_MEMORY(&cpuidRegisters, sizeof(CPUID_REGISTERS));

    // Check if processor supports Intel BMI1 (Bit Manipulation Instruction Set 1)
    // BMI1 is only available since Haswell Intel microarchitecture (2013)
    __cpuidex((int*)&cpuidRegisters, 0x07, 0x00);
    if (_bittest((const LONG*)&cpuidRegisters.dwEBX, 3)) {
        return _bextr_u64(qwValue, dwStart, dwLength); // BEXTR — Bit Field Extract
    }
    else {
        if (dwStart >= 64)
            return 0;

        if (dwLength >= 64)
            return (qwValue >> dwStart);

        return ((qwValue >> dwStart) & ((1ULL << dwLength) - 1));
    }
}

/// @brief Calculate logarithm base 2 of an unsigned 64-bit integer
/// @param qwValue The unsigned 64-bit integer value
/// @return Returns the index of the last bit set/log2 of input value
extern "C" __forceinline DWORD __stdcall binary_logarithm(
    _In_ QWORD qwValue
) {
    // Init local variables
    CPUID_REGISTERS cpuidRegisters; ZERO_MEMORY(&cpuidRegisters, sizeof(CPUID_REGISTERS));
    DWORD dwIndex = 0;

    // Check if processor supports Intel LZCNT (Leading Zero Count) instruction
    // LZCNT is only available since Haswell Intel microarchitecture (2013)
    __cpuidex((int*)&cpuidRegisters, 0x80000001, 0x00);
    if (_bittest((const LONG*)&cpuidRegisters.dwECX, 5)) {
        return ((DWORD)_lzcnt_u64(qwValue) ^ 63); // LZCNT — Count the Number of Leading Zero Bits
    }
    else {
        if (_BitScanReverse64(&dwIndex, qwValue)) // BSR — Bit Scan Reverse
            return dwIndex;
        else
            return 0;
    }
}

/// @brief Create a bitmask whose contiguous lower bits are set to 1 up to the specified bit length
/// @param dwLength The number of bits to be set to 1
/// @return Returns an unsigned 64-bit integer containing the newly created mask
extern "C" __forceinline QWORD __stdcall create_bitmask(
    _In_ DWORD dwLength
) {
    // Init local variables
    CPUID_REGISTERS cpuidRegisters; ZERO_MEMORY(&cpuidRegisters, sizeof(CPUID_REGISTERS));

    // Check if processor supports Intel BMI2 (Bit Manipulation Instruction Set 2)
    // BMI2 is only available since Haswell Intel microarchitecture (2013)
    __cpuidex((int*)&cpuidRegisters, 0x07, 0x00);
    if (_bittest((const LONG*)&cpuidRegisters.dwEBX, 8)) {
        return _bzhi_u64(0xFFFFFFFFFFFFFFFF, dwLength); // BZHI — Zero High Bits Starting with Specified Bit Position
    }
    else {
        if (dwLength >= 64)
            return 0xFFFFFFFFFFFFFFFFULL;

        return ((1ULL << dwLength) - 1);
    }
}

/// @brief Clear contiguous lower bits of an unsigned 64-bit integer up to the specified bit length
/// @param qwValue The unsigned 64-bit integer value
/// @param dwLength The number of bits to be cleared
/// @return Returns an unsigned 64-bit integer whose lower n bits have been cleared
extern "C" __forceinline QWORD __stdcall clear_lower_bits(
    _In_ QWORD qwValue,
    _In_ DWORD dwLength
) {
    // Init local variables
    CPUID_REGISTERS cpuidRegisters; ZERO_MEMORY(&cpuidRegisters, sizeof(CPUID_REGISTERS));
    QWORD qwBitmask = 0;

    // Compute bitmask
    qwBitmask = create_bitmask(dwLength);

    // Check if processor supports Intel BMI1 (Bit Manipulation Instruction Set 1)
    // BMI1 is only available since Haswell Intel microarchitecture (2013)
    __cpuidex((int*)&cpuidRegisters, 0x07, 0x00);
    if (_bittest((const LONG*)&cpuidRegisters.dwEBX, 3)) {
        return _andn_u64(qwBitmask, qwValue); // ANDN — Logical AND NOT
    }
    else {
        return (qwValue & ~qwBitmask);
    }
}

#pragma endregion