# EVENSTAR - PagingDbgExt

## Version
- `v10.5.6`

## Brief
- `ISA: x86`
- `Mode: Long`
- `Bitness: 64-bit`
- `CPL: 3`
- `OS: Windows`
- `Language: C`
- _WdbgExts_ "old style" debugger extension `DLL` that contains various experiments around `IA-32e Paging`

## Usage
- Set up kernel-mode debugging of the target
```
0: kd> vertarget
Windows 10 Kernel Version 22000 MP (2 procs) Free x64
Product: WinNt, suite: TerminalServer SingleUserTS
Edition build lab: 22000.1.amd64fre.co_release.210604-1628
Kernel base = 0xfffff804`6580f000 PsLoadedModuleList = 0xfffff804`66438b90
Debug session time: Tue Jun  3 17:15:28.502 2025 (UTC - 4:00)
System Uptime: 0 days 0:12:56.092

0: kd> .load PagingDbgExt.dll

0: kd> .chain
--snip--
Extension DLL chain:
    PagingDbgExt: API 10.5.6, 
        [path: C:\Users\winterknife\Desktop\Tools\WinDbgExtensions\PagingDbgExt.dll]
--snip--

0: kd> .extmatch /D /e PagingDbgExt *
!PagingDbgExt.check_4_level_paging_mode
!PagingDbgExt.get_kernel_dtb
!PagingDbgExt.get_pml4_autoentry_index
!PagingDbgExt.get_process_dtb
!PagingDbgExt.get_pxe_address
!PagingDbgExt.get_pxe_base
!PagingDbgExt.help

0: kd> !PagingDbgExt.help
Help for debugger extension DLL PagingDbgExt.dll
   help                      - Show help menu
   get_kernel_dtb            - Find the kernel's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for KVAS contained in CR3 from the Low Stub
   get_process_dtb           - Find a process's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for UVAS contained in CR3 from the EPROCESS structure
   check_4_level_paging_mode - Check if the logical processor is using 4-level IA-32e paging mode
   get_pml4_autoentry_index  - Find the self-reference entry/auto-entry index of the Page Map Level 4 (PML4) table from the CR3
   get_pxe_base              - Compute the starting KVA of the paging structure entry (PxE) range from the PML4 table auto-entry index
   get_pxe_address           - Compute the KVA of the paging structure entry (PxE) that maps the specified VA from the PML4 table auto-entry index

0: kd> !PagingDbgExt.get_kernel_dtb
[+] nt!_PROCESSOR_START_BLOCK structure found at PA=0x13000
[+] HAL Heap base KVA=0xFFFFF7C440000000
[+] nt!_PROCESSOR_START_BLOCK.ProcessorState.SpecialRegisters.Cr3=0x1AE000

0: kd> ? poi(nt!HalpLowStubPhysicalAddress)
Evaluate expression: 77824 = 00000000`00013000

0: kd> ? poi(nt!HalpOriginalHeapStart)
Evaluate expression: -9052717318144 = fffff7c4`40000000

0: kd> r @cr3
cr3=00000000001ae000

0: kd> !process 4 0
Searching for Process with Cid == 4
PROCESS ffffc4866e2ab040
    SessionId: none  Cid: 0004    Peb: 00000000  ParentCid: 0000
    DirBase: 001ae000  ObjectTable: ffffe7876f403dc0  HandleCount: 1970.
    Image: System

0: kd> dt nt!_KPROCESS ffffc4866e2ab040 DirectoryTableBase
   +0x028 DirectoryTableBase : 0x1ae000

0: kd> dt /p nt!_KPROCESSOR_STATE 0x13090 SpecialRegisters.Cr3
   +0x000 SpecialRegisters     : 
      +0x010 Cr3                  : 0x1ae000

0: kd> !db 0x13000
#   13000 e9 4d 06 00 01 00 00 00-01 00 00 00 3f 00 18 30 .M..........?..0
#   13010 01 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00 ................
#   13020 00 00 00 00 00 00 00 00-00 00 00 00 00 9b 20 00 .............. .
#   13030 00 00 00 00 00 00 00 00-ff ff 00 00 00 93 cf 00 ................
#   13040 00 00 00 00 00 00 00 00-ff ff 00 00 00 9b cf 00 ................
#   13050 00 00 00 00 00 00 00 00-00 90 4f 79 00 00 00 00 ..........Oy....
#   13060 79 36 01 00 30 00 d7 36-01 00 10 00 00 00 00 00 y6..0..6........
#   13070 70 18 c2 65 04 f8 ff ff-00 c0 00 40 c4 f7 ff ff p..e.......@....

0: kd> db poi(nt!HalpLowStub)
fffff7c4`4000c000  e9 4d 06 00 01 00 00 00-01 00 00 00 3f 00 18 30  .M..........?..0
fffff7c4`4000c010  01 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
fffff7c4`4000c020  00 00 00 00 00 00 00 00-00 00 00 00 00 9b 20 00  .............. .
fffff7c4`4000c030  00 00 00 00 00 00 00 00-ff ff 00 00 00 93 cf 00  ................
fffff7c4`4000c040  00 00 00 00 00 00 00 00-ff ff 00 00 00 9b cf 00  ................
fffff7c4`4000c050  00 00 00 00 00 00 00 00-00 90 4f 79 00 00 00 00  ..........Oy....
fffff7c4`4000c060  79 36 01 00 30 00 d7 36-01 00 10 00 00 00 00 00  y6..0..6........
fffff7c4`4000c070  70 18 c2 65 04 f8 ff ff-00 c0 00 40 c4 f7 ff ff  p..e.......@....

0: kd> dps poi(nt!HalpLowStub) L10
fffff7c4`4000c000  00000001`00064de9
fffff7c4`4000c008  3018003f`00000001
fffff7c4`4000c010  00000000`00000001
fffff7c4`4000c018  00000000`00000000
fffff7c4`4000c020  00000000`00000000
fffff7c4`4000c028  00209b00`00000000
fffff7c4`4000c030  00000000`00000000
fffff7c4`4000c038  00cf9300`0000ffff
fffff7c4`4000c040  00000000`00000000
fffff7c4`4000c048  00cf9b00`0000ffff
fffff7c4`4000c050  00000000`00000000
fffff7c4`4000c058  00000000`794f9000
fffff7c4`4000c060  36d70030`00013679
fffff7c4`4000c068  00000000`00100001
fffff7c4`4000c070  fffff804`65c21870 nt!HalpLMStub
fffff7c4`4000c078  fffff7c4`4000c000

0: kd> !pte poi(nt!HalpLowStub)
                                           VA fffff7c44000c000
PXE at FFFFF97CBE5F2F78    PPE at FFFFF97CBE5EF888    PDE at FFFFF97CBDF11000    PTE at FFFFF97BE2200060
contains 0000000002182063  contains 8000000002185063  contains 8000000002186063  contains 8000000000013963
pfn 2182      ---DA--KWEV  pfn 2185      ---DA--KW-V  pfn 2186      ---DA--KW-V  pfn 13        -G-DA--KW-V

0: kd> !vtop 0x1ae000 0xfffff7c44000c000
Amd64VtoP: Virt fffff7c44000c000, pagedir 00000000001ae000
Amd64VtoP: PML4E 00000000001aef78
Amd64VtoP: PDPE 0000000002182888
Amd64VtoP: PDE 0000000002185000
Amd64VtoP: PTE 0000000002186060
Amd64VtoP: Mapped phys 0000000000013000
Virtual address fffff7c44000c000 translates to physical address 13000.

0: kd> !process 0 0 lsass.exe
PROCESS ffffc4866ede80c0
    SessionId: 0  Cid: 02e8    Peb: 414677f000  ParentCid: 0208
    DirBase: 7dec0000  ObjectTable: ffffe78771c7b2c0  HandleCount: 926.
    Image: lsass.exe

0: kd> !PagingDbgExt.get_process_dtb 0xffffc4866ede80c0
[*] nt!_EPROCESS KVA=0xFFFFC4866EDE80C0
[+] nt!_EPROCESS.Pcb.DirectoryTableBase=0x7DEC0000

0: kd> !PagingDbgExt.check_4_level_paging_mode
[!] Current processor number = 0
[+] 4-level IA-32e paging mode is enabled!

0: kd> !PagingDbgExt.get_pml4_autoentry_index 0x1AE000
[!] Current processor number = 0
[+] 4-level IA-32e paging mode is enabled!
[*] CR3=0x1AE000
[+] Page Map Level 4 (PML4) table base PA=0x1AE000
[+] PML4 auto-entry found at index: 0x1F2 (0n498)

0: kd> ? (poi(nt!MmPteBase) >> 0n39) & 0x1ff
Evaluate expression: 498 = 00000000`000001f2

0: kd> !PagingDbgExt.get_pxe_base 0x1F2
[!] Current processor number = 0
[+] 4-level IA-32e paging mode is enabled!
[*] PML4 table auto-entry index: 0x1F2 (0n498)
[+] PTE_BASE=0xFFFFF90000000000
[+] PDE_BASE=0xFFFFF97C80000000
[+] PPE_BASE=0xFFFFF97CBE400000
[+] PXE_BASE=0xFFFFF97CBE5F2000
[+] PXE_SELFMAP=0xFFFFF97CBE5F2F90
[+] PXE_TOP=0xFFFFF97CBE5F2FFF
[+] PPE_TOP=0xFFFFF97CBE5FFFFF
[+] PDE_TOP=0xFFFFF97CBFFFFFFF
[+] PTE_TOP=0xFFFFF97FFFFFFFFF

0: kd> ? poi(nt!MmPteBase)
Evaluate expression: -7696581394432 = fffff900`00000000

0: kd> uf nt!MiGetPteAddress
nt!MiGetPteAddress:
fffff804`65b20f90 48c1e909        shr     rcx,9
fffff804`65b20f94 48b8f8ffffff7f000000 mov rax,7FFFFFFFF8h
fffff804`65b20f9e 4823c8          and     rcx,rax
fffff804`65b20fa1 48b80000000000f9ffff mov rax,0FFFFF90000000000h
fffff804`65b20fab 4803c1          add     rax,rcx
fffff804`65b20fae c3              ret

0: kd> uf nt!MiGetPdeAddress
nt!MiGetPdeAddress:
fffff804`65ae0420 48c1e912        shr     rcx,12h
fffff804`65ae0424 81e1f8ffff3f    and     ecx,3FFFFFF8h
fffff804`65ae042a 48b8000000807cf9ffff mov rax,0FFFFF97C80000000h
fffff804`65ae0434 4803c1          add     rax,rcx
fffff804`65ae0437 c3              ret

0: kd> rdmsr 0xC0000082
msr[c0000082] = fffff804`65c37bc0

0: kd> !PagingDbgExt.get_pxe_address 0xfffff80465c37bc0 0x1f2
[!] Current processor number = 0
[+] 4-level IA-32e paging mode is enabled!
[*] VA=0xFFFFF80465C37BC0
[*] PML4 table auto-entry index: 0x1F2 (0n498)
[+] PTE KVA=0xFFFFF97C0232E1B8
[+] PDE KVA=0xFFFFF97CBE011970
[+] PPE KVA=0xFFFFF97CBE5F0088
[+] PXE KVA=0xFFFFF97CBE5F2F80

0: kd> !pte 0xfffff80465c37bc0
                                           VA fffff80465c37bc0
PXE at FFFFF97CBE5F2F80    PPE at FFFFF97CBE5F0088    PDE at FFFFF97CBE011970    PTE at FFFFF97C0232E1B8
contains 000000000218B063  contains 000000000218C063  contains 000000000219C063  contains 090000007F05C121
pfn 218b      ---DA--KWEV  pfn 218c      ---DA--KWEV  pfn 219c      ---DA--KWEV  pfn 7f05c     -G--A--KREV

0: kd> !pte 0xFFFFF97CBE011970
                                           VA fffff97c0232e000
PXE at FFFFF97CBE5F2F90    PPE at FFFFF97CBE5F2F80    PDE at FFFFF97CBE5F0088    PTE at FFFFF97CBE011970
contains 80000000001AE063  contains 000000000218B063  contains 000000000218C063  contains 000000000219C063
pfn 1ae       ---DA--KW-V  pfn 218b      ---DA--KWEV  pfn 218c      ---DA--KWEV  pfn 219c      ---DA--KWEV

0: kd> .unload PagingDbgExt.dll
Unloading PagingDbgExt extension DLL
```

## Notes
Since publishing this on Twitter, I have received some valid criticism from [sixtyvividtails](https://x.com/sixtyvividtails) (who btw you should follow if you are into low-level `Wintel` stuff).

You can read what they wrote [here](https://github.com/winterknife/EVENSTAR/issues/1).

Ultimately, this is a rehash of the technique that was first discovered by [Alex Ionescu](https://x.com/aionescu) and originally implemented by [Ulf Frisk](https://x.com/ulffrisk).

I don't plan on improving the heuristics at the moment but you reading this should make the changes (or at least know what might fail and what could be improved).

## Tested OS Versions
- `Windows 11 21H2 Build 22000 Revision 675 64-bit`

## References
1. [Getting Physical with USB Type-C: Windows 10 RAM Forensics and UEFI Attacks - Alex Ionescu](http://publications.alex-ionescu.com/Recon/ReconBru%202017%20-%20Getting%20Physical%20with%20USB%20Type-C,%20Windows%2010%20RAM%20Forensics%20and%20UEFI%20Attacks.pdf)
2. [VmmWinInit_DTB_FindValidate_X64_LowStub](https://github.com/ufrisk/MemProcFS/blob/master/vmm/vmmwininit.c#L801)
3. [find_low_stub](https://github.com/chompie1337/SMBGhost_RCE_PoC/blob/master/exploit.py#L396)
4. [DriverInitPageTableBase](https://github.com/Cr4sh/KernelForge/blob/master/kforge_driver/kforge_driver.cpp#L60)
5. [WinIoQueryPML4Value](https://github.com/hfiref0x/WinObjEx64/blob/master/Source/WinObjEx64/drivers/winio.c#L188)
6. [Some toying with the Self-Reference PML4 Entry](https://blahcat.github.io/2020-06-15-playing-with-self-reference-pml4-entry/)
7. [Getting Physical: Extreme abuse of Intel based Paging Systems - Part 1](https://www.coresecurity.com/core-labs/articles/getting-physical-extreme-abuse-of-intel-based-paging-systems-part-1)
8. [Getting Physical: Extreme abuse of Intel based Paging Systems - Part 2 - Windows](https://www.coresecurity.com/core-labs/articles/getting-physical-extreme-abuse-of-intel-based-paging-systems-part-2-windows)
9. [Getting Physical: Extreme abuse of Intel based Paging Systems - Part 3 - Windows HAL's Heap](https://www.coresecurity.com/core-labs/articles/getting-physical-extreme-abuse-of-intel-based-paging-systems)
10. [Windows 8 Kernel Memory Protections Bypass](https://labs.withsecure.com/publications/windows-8-kernel-memory-protections-bypass)
11. [Virtual Memory - Intro to Paging Tables](https://blog.back.engineering/23/08/2020/)
12. [What Makes It Page?: The Windows 7 (x64) Virtual Memory Manager](https://www.amazon.ca/What-Makes-Page-Windows-Virtual/dp/1479114294)