# EVENSTAR - PagingDbgExt

## Version
- `v10.6.6`

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
1: kd> vertarget
Windows 10 Kernel Version 22000 MP (2 procs) Free x64
Product: WinNt, suite: TerminalServer SingleUserTS
Edition build lab: 22000.1.amd64fre.co_release.210604-1628
Kernel base = 0xfffff804`4fe00000 PsLoadedModuleList = 0xfffff804`50a29b90
Debug session time: Sun Jun 15 14:17:31.297 2025 (UTC - 4:00)
System Uptime: 0 days 3:37:31.814

1: kd> .load PagingDbgExt.dll

1: kd> .chain
--snip--
Extension DLL chain:
    PagingDbgExt: API 10.6.6, 
        [path: C:\Users\winterknife\Desktop\Tools\WinDbgExtensions\PagingDbgExt.dll]
--snip--

1: kd> .extmatch /D /e PagingDbgExt *
!PagingDbgExt.check_4_level_paging_mode
!PagingDbgExt.get_kernel_dtb
!PagingDbgExt.get_physical_address
!PagingDbgExt.get_pml4_autoentry_index
!PagingDbgExt.get_process_dtb
!PagingDbgExt.get_pxe_address
!PagingDbgExt.get_pxe_base
!PagingDbgExt.help

1: kd> !PagingDbgExt.help
Help for debugger extension DLL PagingDbgExt.dll
   help                      - Show help menu
   get_kernel_dtb            - Find the kernel's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for KVAS contained in CR3 from the Low Stub
   get_process_dtb           - Find a process's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for UVAS contained in CR3 from the EPROCESS structure
   check_4_level_paging_mode - Check if the logical processor is using 4-level IA-32e paging mode
   get_pml4_autoentry_index  - Find the self-reference entry/auto-entry index of the Page Map Level 4 (PML4) table from the CR3
   get_pxe_base              - Compute the starting KVA of the paging structure entry (PxE) range from the PML4 table auto-entry index
   get_pxe_address           - Compute the KVA of the paging structure entry (PxE) that maps the specified VA from the PML4 table auto-entry index
   get_physical_address      - Translate the specified linear address (VA) to its mapped physical address (PA) and determine the VA's access rights from the CR3

1: kd> !PagingDbgExt.get_kernel_dtb
[+] nt!_PROCESSOR_START_BLOCK structure found at PA=0x13000
[+] HAL Heap base KVA=0xFFFFF7D980000000
[+] nt!_PROCESSOR_START_BLOCK.ProcessorState.SpecialRegisters.Cr3=0x1AE000

1: kd> ? poi(nt!HalpLowStubPhysicalAddress)
Evaluate expression: 77824 = 00000000`00013000

1: kd> ? poi(nt!HalpOriginalHeapStart)
Evaluate expression: -8961449263104 = fffff7d9`80000000

1: kd> dt /p nt!_KPROCESSOR_STATE 0x13090 SpecialRegisters.Cr3
   +0x000 SpecialRegisters     : 
      +0x010 Cr3                  : 0x1ae000

1: kd> r @cr3
cr3=00000000001ae000

1: kd> !process 4 0
Searching for Process with Cid == 4
PROCESS ffff8088a80af040
    SessionId: none  Cid: 0004    Peb: 00000000  ParentCid: 0000
    DirBase: 001ae000  ObjectTable: ffffcf03a6203dc0  HandleCount: 2209.
    Image: System

1: kd> dps poi(nt!HalpLowStub) L10
fffff7d9`8000c000  00000001`00064de9
fffff7d9`8000c008  3018003f`00000001
fffff7d9`8000c010  00000000`00000001
fffff7d9`8000c018  00000000`00000000
fffff7d9`8000c020  00000000`00000000
fffff7d9`8000c028  00209b00`00000000
fffff7d9`8000c030  00000000`00000000
fffff7d9`8000c038  00cf9300`0000ffff
fffff7d9`8000c040  00000000`00000000
fffff7d9`8000c048  00cf9b00`0000ffff
fffff7d9`8000c050  00000000`00000000
fffff7d9`8000c058  00000000`bffff000
fffff7d9`8000c060  36d70030`00013679
fffff7d9`8000c068  00000000`00100001
fffff7d9`8000c070  fffff804`50212870 nt!HalpLMStub
fffff7d9`8000c078  fffff7d9`8000c000

1: kd> !process 0 0 lsass.exe
PROCESS ffff8088a8b26080
    SessionId: 0  Cid: 02e4    Peb: 9c876d1000  ParentCid: 0210
    DirBase: 10f8f1000  ObjectTable: ffffcf03a8a81280  HandleCount: 999.
    Image: lsass.exe

1: kd> !PagingDbgExt.get_process_dtb 0xffff8088a8b26080
[*] nt!_EPROCESS KVA=0xFFFF8088A8B26080
[+] nt!_EPROCESS.Pcb.DirectoryTableBase=0x10F8F1000

1: kd> !PagingDbgExt.check_4_level_paging_mode
[!] Current processor number = 1
[+] 4-level IA-32e paging mode is enabled!

1: kd> !PagingDbgExt.get_pml4_autoentry_index 0x1AE000
[!] Current processor number = 1
[+] 4-level IA-32e paging mode is enabled!
[*] CR3=0x1AE000
[+] Page Map Level 4 (PML4) table base PA=0x1AE000
[+] PML4 auto-entry found at index: 0x151 (0n337)

1: kd> ? (poi(nt!MmPteBase) >> 0n39) & 0x1ff
Evaluate expression: 337 = 00000000`00000151

1: kd> !PagingDbgExt.get_pxe_base 0x151
[!] Current processor number = 1
[+] 4-level IA-32e paging mode is enabled!
[*] PML4 table auto-entry index: 0x151 (0n337)
[+] PTE_BASE=0xFFFFA88000000000
[+] PDE_BASE=0xFFFFA8D440000000
[+] PPE_BASE=0xFFFFA8D46A200000
[+] PXE_BASE=0xFFFFA8D46A351000
[+] PXE_SELFMAP=0xFFFFA8D46A351A88
[+] PXE_TOP=0xFFFFA8D46A351FFF
[+] PPE_TOP=0xFFFFA8D46A3FFFFF
[+] PDE_TOP=0xFFFFA8D47FFFFFFF
[+] PTE_TOP=0xFFFFA8FFFFFFFFFF

1: kd> ? poi(nt!MmPteBase)
Evaluate expression: -96207267430400 = ffffa880`00000000

1: kd> uf nt!MiGetPteAddress
nt!MiGetPteAddress:
fffff804`50111f90 48c1e909        shr     rcx,9
fffff804`50111f94 48b8f8ffffff7f000000 mov rax,7FFFFFFFF8h
fffff804`50111f9e 4823c8          and     rcx,rax
fffff804`50111fa1 48b80000000080a8ffff mov rax,0FFFFA88000000000h
fffff804`50111fab 4803c1          add     rax,rcx
fffff804`50111fae c3              ret

1: kd> uf nt!MiGetPdeAddress
nt!MiGetPdeAddress:
fffff804`500d1420 48c1e912        shr     rcx,12h
fffff804`500d1424 81e1f8ffff3f    and     ecx,3FFFFFF8h
fffff804`500d142a 48b800000040d4a8ffff mov rax,0FFFFA8D440000000h
fffff804`500d1434 4803c1          add     rax,rcx
fffff804`500d1437 c3              ret

1: kd> !PagingDbgExt.get_pxe_address 0xFFFFF78000000000 0x151
[!] Current processor number = 1
[+] 4-level IA-32e paging mode is enabled!
[*] VA=0xFFFFF78000000000
[*] PML4 table auto-entry index: 0x151 (0n337)
[+] PTE KVA=0xFFFFA8FBC0000000
[+] PDE KVA=0xFFFFA8D47DE00000
[+] PPE KVA=0xFFFFA8D46A3EF000
[+] PXE KVA=0xFFFFA8D46A351F78

1: kd> !pte 0xFFFFF78000000000
                                           VA fffff78000000000
PXE at FFFFA8D46A351F78    PPE at FFFFA8D46A3EF000    PDE at FFFFA8D47DE00000    PTE at FFFFA8FBC0000000
contains 000000000F202063  contains 000000000F203063  contains 000000000F204063  contains 800000000F22C963
pfn f202      ---DA--KWEV  pfn f203      ---DA--KWEV  pfn f204      ---DA--KWEV  pfn f22c      -G-DA--KW-V

1: kd> rdmsr 0xC0000082
msr[c0000082] = fffff804`50228bc0

1: kd> !PagingDbgExt.get_physical_address 0xfffff80450228bc0 0x1ae000
[!] Current processor number = 1
[+] 4-level IA-32e paging mode is enabled!
[*] VA=0xFFFFF80450228BC0
[*] CR3=0x1AE000
[+] PML4 table base PA=0x1AE000
[+] PML4 index: 0x1F0 (0n496)
[+] PML4E PA=0x1AEF80
[+] PML4E contents=0xF20B063
[+] PDPT base PA=0xF20B000
[+] PDPT index: 0x11 (0n17)
[+] PDPTE PA=0xF20B088
[+] PDPTE contents=0xF20C063
[+] PD table base PA=0xF20C000
[+] PD index: 0x81 (0n129)
[+] PDE PA=0xF20C408
[+] PDE contents=0xA000001008001A1
[+] 2 MB physical page base PA=0x100800000
[+] 2 MB physical page offset: 0x28BC0 (0n166848)
[+] PA=0x100828BC0
[+] Read-only address.
[+] Supervisor-mode address.
[+] Executable address.
[+] Dirty: 0
[+] Global: 1

1: kd> !vtop 0x1ae000 0xfffff80450228bc0
Amd64VtoP: Virt fffff80450228bc0, pagedir 00000000001ae000
Amd64VtoP: PML4E 00000000001aef80
Amd64VtoP: PDPE 000000000f20b088
Amd64VtoP: PDE 000000000f20c408
Amd64VtoP: Large page mapped phys 0000000100828bc0
Virtual address fffff80450228bc0 translates to physical address 100828bc0.

1: kd> !pte fffff804`50228bc0
                                           VA fffff80450228bc0
PXE at FFFFA8D46A351F80    PPE at FFFFA8D46A3F0088    PDE at FFFFA8D47E011408    PTE at FFFFA8FC02281140
contains 000000000F20B063  contains 000000000F20C063  contains 0A000001008001A1  contains 0000000000000000
pfn f20b      ---DA--KWEV  pfn f20c      ---DA--KWEV  pfn 100800    -GL-A--KREV  LARGE PAGE pfn 100828

1: kd> .unload PagingDbgExt.dll
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
13. [Circumventing Leak Restrictions and Breaking KASLR on Windows 11 24H2 using an HVCI-compatible Driver with Physical Memory Access](https://xacone.github.io/kaslr_leak_24h2.html)
14. [Windows Address Translation Deep Dive – Part 1](https://bsodtutorials.wordpress.com/2021/06/14/windows-address-translation-deep-dive-part-1/)
15. [Windows Address Translation Deep Dive – Part 2](https://bsodtutorials.wordpress.com/2024/04/05/windows-address-translation-deep-dive-part-2/)
16. [Windows Address Translation Deep Dive – Part 3](https://bsodtutorials.wordpress.com/2024/05/14/windows-address-translation-deep-dive-part-3/)
17. [Windows Memory Introspection with IceBox](https://blog.thalium.re/posts/windows-full-memory-introspection-with-icebox/)
18. [Windows Virtual Address Translation and the Pagefile.](https://web.archive.org/web/20200120124724/http://blog.rekall-forensic.com/2014/10/windows-virtual-address-translation-and.html)
19. [Windows 10 KVAS and Software SMEP](https://wumb0.in/windows-10-kvas-and-software-smep.html)
20. [MMPTE_HARDWARE](https://www.geoffchappell.com/studies/windows/km/ntoskrnl/api/mm/mi/mmpte/hardware.htm)
21. [Virtual Memory, Page Tables, and One Bit - CVE-2016-7255](https://ricklarabee.blogspot.com/2017/01/virtual-memory-page-tables-and-one-bit.html)
22. [Windows 10 HAL’s Heap – Extinction of the "HalpInterruptController" Table Exploitation Technique](https://labs.bluefrostsecurity.de/blog/2017/05/11/windows-10-hals-heap-extinction-of-the-halpinterruptcontroller-table-exploitation-technique/)
23. [Meltdown Reloaded: Breaking Windows KASLR by Leaking KVA Shadow Mappings](https://labs.bluefrostsecurity.de/blog/2020/06/30/meltdown-reloaded-breaking-windows-kaslr/)
24. [Turning the Pages: Introduction to Memory Paging on Windows 10 x64](https://connormcgarr.github.io/paging/)
25. [Exploit Development: Leveraging Page Table Entries for Windows Kernel Exploitation](https://connormcgarr.github.io/pte-overwrites/)
26. [Page Table: From Virtual to Physical](https://dx9.uk/posts/physical-memory/)
27. [Direct Page Manipulation (DPM)](https://github.com/SamuelTulach/DirectPageManipulation)
28. [anyvtop](https://github.com/kkent030315/anyvtop)
29. [PageTableInjection](https://github.com/kkent030315/PageTableInjection)
30. [PTView](https://github.com/VollRagm/PTView)
31. [PTM - Page Table Manipulation From Usermode](https://blog.back.engineering/01/12/2020/)
32. [Making something out of Zeros: Alternative primitive for Windows Kernel Exploitation](https://www.coresecurity.com/core-labs/articles/making-something-out-zeros-alternative-primitive-windows-kernel-exploitation)
33. [pagewalkr](https://github.com/Deputation/pagewalkr)
34. [Paging](https://shhoya.github.io/hv_paging.html)
35. [Demystifying Physical Memory Primitive Exploitation on Windows](https://0dr3f.github.io/Demystifying_Physical_Memory_Primitive_Exploitation_on_Windows)
36. [Intel® 64 and IA-32 Architectures Software Developer Manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
37. [PTEditor](https://github.com/misc0110/PTEditor)