// ========================================================================
// File: GetKernelDirectoryTableBase.h
//
// Author: winterknife
//
// Description: Header file for GetKernelDirectoryTableBase.cpp source file
//
// Modifications:
//  2025-05-13	Created
//  2025-05-18  Updated
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

#define PSB_GDT32_NULL      0 * 16
#define PSB_GDT32_CODE64    1 * 16
#define PSB_GDT32_DATA32    2 * 16
#define PSB_GDT32_CODE32    3 * 16
#define PSB_GDT32_MAX       3

#define KUSER_SHARED_DATA_RO_MAPPING_X64_KVA 0xFFFFF78000000000
#define ACTIVEPROCESSORCOUNT_OFFSET          0x03C0

#pragma endregion

// ========================================================================
// Structures/Enumerations/Unions
// ========================================================================

#pragma region STRUCTS_ENUMS_UNIONS

#pragma pack(push, 2)
typedef struct _FAR_JMP_16 {
    UCHAR  OpCode; // opcode = 0xE9
    USHORT Offset;
} FAR_JMP_16, *PFAR_JMP_16;

typedef struct _FAR_TARGET_32 {
    ULONG  Offset;
    USHORT Selector;
} FAR_TARGET_32, *PFAR_TARGET_32;

typedef struct _PSEUDO_DESCRIPTOR_32 {
    USHORT Limit;
    ULONG  Base;
} PSEUDO_DESCRIPTOR_32, *PPSEUDO_DESCRIPTOR_32;
#pragma pack(pop)

// 0x10 bytes (sizeof)
#pragma warning(push)
#pragma warning(disable: 4201) // anonymous unions warning
typedef union _KGDTENTRY64 {
    struct {
        USHORT  LimitLow;
        USHORT  BaseLow;
        union {
            struct {
                UCHAR   BaseMiddle;
                UCHAR   Flags1;
                UCHAR   Flags2;
                UCHAR   BaseHigh;
            } Bytes;
            struct {
                ULONG   BaseMiddle : 8;
                ULONG   Type : 5;
                ULONG   Dpl : 2;
                ULONG   Present : 1;
                ULONG   LimitHigh : 4;
                ULONG   System : 1;
                ULONG   LongMode : 1;
                ULONG   DefaultBig : 1;
                ULONG   Granularity : 1;
                ULONG   BaseHigh : 8;
            } Bits;
        };
        ULONG BaseUpper;
        ULONG MustBeZero;
    };
    ULONG64 Alignment;
} KGDTENTRY64, *PKGDTENTRY64;
#pragma warning(pop)

typedef struct _KDESCRIPTOR {
    USHORT Pad[3];
    USHORT Limit;
    PVOID  Base;
} KDESCRIPTOR, *PKDESCRIPTOR;

typedef struct _KSPECIAL_REGISTERS {
    ULONG64     Cr0;
    ULONG64     Cr2;
    ULONG64     Cr3;
    ULONG64     Cr4;
    ULONG64     KernelDr0;
    ULONG64     KernelDr1;
    ULONG64     KernelDr2;
    ULONG64     KernelDr3;
    ULONG64     KernelDr6;
    ULONG64     KernelDr7;
    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;
    USHORT      Tr;
    USHORT      Ldtr;
    ULONG       MxCsr;
    ULONG64     DebugControl;
    ULONG64     LastBranchToRip;
    ULONG64     LastBranchFromRip;
    ULONG64     LastExceptionToRip;
    ULONG64     LastExceptionFromRip;
    ULONG64     Cr8;
    ULONG64     MsrGsBase;
    ULONG64     MsrGsSwap;
    ULONG64     MsrStar;
    ULONG64     MsrLStar;
    ULONG64     MsrCStar;
    ULONG64     MsrSyscallMask;
    ULONG64     Xcr0;
    ULONG64     MsrFsBase;
    ULONG64     SpecialPadding0;
} KSPECIAL_REGISTERS, *PKSPECIAL_REGISTERS;

typedef struct _KPROCESSOR_STATE {
    KSPECIAL_REGISTERS SpecialRegisters;
    CONTEXT            ContextFrame;
} KPROCESSOR_STATE, *PKPROCESSOR_STATE;

// nt!HalpLowStub
typedef struct _PROCESSOR_START_BLOCK* PPROCESSOR_START_BLOCK;
typedef struct _PROCESSOR_START_BLOCK {
    FAR_JMP_16             Jmp; // The block starts with a jmp instruction to the end of the block
    ULONG                  CompletionFlag; // Completion flag is set to non-zero when the target processor has started
    PSEUDO_DESCRIPTOR_32   Gdt32; // Pseudo descriptors for GDT
    PSEUDO_DESCRIPTOR_32   Idt32; // Pseudo descriptors for IDT
    KGDTENTRY64            Gdt[PSB_GDT32_MAX + 1]; // The temporary 32-bit GDT itself resides here
    ULONG64                TiledCr3; // Physical address of the 64-bit top-level identity-mapped page table
    FAR_TARGET_32          PmTarget; // Far jump target from Rm to Pm code
    FAR_TARGET_32          LmIdentityTarget; // Far jump target from Pm to Lm code
    PVOID                  LmTarget; // Address of LmTarget
    PPROCESSOR_START_BLOCK SelfMap; // Linear address of this structure
    ULONG64                MsrPat; // Contents of the PAT msr
    ULONG64                MsrEFER; // Contents of the EFER msr
    KPROCESSOR_STATE       ProcessorState; // Initial processor state for the processor to be started
} PROCESSOR_START_BLOCK;

#pragma endregion

// ========================================================================
// C routine declarations
// ========================================================================

#pragma region DECLARATIONS

/// @brief Built-in command to find the kernel's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for KVAS contained in CR3 from the Low Stub
/// @param hCurrentProcess Handle for the current process
/// @param hCurrentThread Handle for the current thread
/// @param qwCurrentPc Program counter
/// @param dwProcessor Current processor
/// @param strArgs Command line arguments
/// @return None
extern "C" __declspec(dllexport) VOID __stdcall get_kernel_dtb(
    _In_   HANDLE hCurrentProcess,
    _In_   HANDLE hCurrentThread,
    _In_   QWORD  qwCurrentPc,
    _In_   DWORD  dwProcessor,
    _In_z_ PCSTR  strArgs
);

#pragma endregion