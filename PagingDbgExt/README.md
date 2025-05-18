# EVENSTAR - PagingDbgExt

## Version
- `v10.0.6`

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
Kernel base = 0xfffff804`4b40f000 PsLoadedModuleList = 0xfffff804`4c038b90
Debug session time: Sun May 18 13:37:25.707 2025 (UTC - 4:00)
System Uptime: 0 days 3:28:02.923

0: kd> .load PagingDbgExt.dll

0: kd> .chain
--snip--
Extension DLL chain:
    PagingDbgExt: API 10.0.6, 
        [path: C:\Users\winterknife\Desktop\Tools\WinDbgExtensions\PagingDbgExt.dll]
--snip--

0: kd> .extmatch /D /e PagingDbgExt *
!PagingDbgExt.get_kernel_dtb
!PagingDbgExt.help

0: kd> !PagingDbgExt.help
Help for debugger extension DLL PagingDbgExt.dll
   help           - Show help menu
   get_kernel_dtb - Find the kernel's DTB (DirectoryTableBase) which is the physical address of the base of the paging-structure hierarchy for KVAS contained in CR3 from the Low Stub

0: kd> !PagingDbgExt.get_kernel_dtb
[+] nt!_PROCESSOR_START_BLOCK structure found at PA=0x13000
[+] HAL Heap base KVA=0xFFFFF7F000000000
[+] nt!_PROCESSOR_START_BLOCK.ProcessorState.SpecialRegisters.Cr3=0x1AE000

0: kd> ? poi(nt!HalpLowStubPhysicalAddress)
Evaluate expression: 77824 = 00000000`00013000

0: kd> ? poi(nt!HalpOriginalHeapStart)
Evaluate expression: -8864812498944 = fffff7f0`00000000

0: kd> r @cr3
cr3=00000000001ae000

0: kd> !process 4 0
Searching for Process with Cid == 4
PROCESS ffffce849b2f1040
    SessionId: none  Cid: 0004    Peb: 00000000  ParentCid: 0000
    DirBase: 001ae000  ObjectTable: ffffaa0c84203dc0  HandleCount: 1818.
    Image: System

0: kd> dt nt!_KPROCESS ffffce849b2f1040 DirectoryTableBase
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
#   13050 00 00 00 00 00 00 00 00-00 20 af 7a 00 00 00 00 ......... .z....
#   13060 79 36 01 00 30 00 d7 36-01 00 10 00 00 00 00 00 y6..0..6........
#   13070 70 18 82 4b 04 f8 ff ff-00 c0 00 00 f0 f7 ff ff p..K............

0: kd> db poi(nt!HalpLowStub)
fffff7f0`0000c000  e9 4d 06 00 01 00 00 00-01 00 00 00 3f 00 18 30  .M..........?..0
fffff7f0`0000c010  01 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
fffff7f0`0000c020  00 00 00 00 00 00 00 00-00 00 00 00 00 9b 20 00  .............. .
fffff7f0`0000c030  00 00 00 00 00 00 00 00-ff ff 00 00 00 93 cf 00  ................
fffff7f0`0000c040  00 00 00 00 00 00 00 00-ff ff 00 00 00 9b cf 00  ................
fffff7f0`0000c050  00 00 00 00 00 00 00 00-00 20 af 7a 00 00 00 00  ......... .z....
fffff7f0`0000c060  79 36 01 00 30 00 d7 36-01 00 10 00 00 00 00 00  y6..0..6........
fffff7f0`0000c070  70 18 82 4b 04 f8 ff ff-00 c0 00 00 f0 f7 ff ff  p..K............

0: kd> dps poi(nt!HalpLowStub) L10
fffff7f0`0000c000  00000001`00064de9
fffff7f0`0000c008  3018003f`00000001
fffff7f0`0000c010  00000000`00000001
fffff7f0`0000c018  00000000`00000000
fffff7f0`0000c020  00000000`00000000
fffff7f0`0000c028  00209b00`00000000
fffff7f0`0000c030  00000000`00000000
fffff7f0`0000c038  00cf9300`0000ffff
fffff7f0`0000c040  00000000`00000000
fffff7f0`0000c048  00cf9b00`0000ffff
fffff7f0`0000c050  00000000`00000000
fffff7f0`0000c058  00000000`7aaf2000
fffff7f0`0000c060  36d70030`00013679
fffff7f0`0000c068  00000000`00100001
fffff7f0`0000c070  fffff804`4b821870 nt!HalpLMStub
fffff7f0`0000c078  fffff7f0`0000c000

0: kd> !pte poi(nt!HalpLowStub)
                                           VA fffff7f00000c000
PXE at FFFFBA5D2E974F78    PPE at FFFFBA5D2E9EFE00    PDE at FFFFBA5D3DFC0000    PTE at FFFFBA7BF8000060
contains 0000000002182063  contains 8000000002185063  contains 8000000002186063  contains 8000000000013963
pfn 2182      ---DA--KWEV  pfn 2185      ---DA--KW-V  pfn 2186      ---DA--KW-V  pfn 13        -G-DA--KW-V

0: kd> !vtop 0x1ae000 0xfffff7f00000c000
Amd64VtoP: Virt fffff7f00000c000, pagedir 00000000001ae000
Amd64VtoP: PML4E 00000000001aef78
Amd64VtoP: PDPE 0000000002182e00
Amd64VtoP: PDE 0000000002185000
Amd64VtoP: PTE 0000000002186060
Amd64VtoP: Mapped phys 0000000000013000
Virtual address fffff7f00000c000 translates to physical address 13000.

0: kd> .unload PagingDbgExt.dll
Unloading PagingDbgExt extension DLL
```

## Tested OS Versions
- `Windows 11 21H2 Build 22000 Revision 675 64-bit`

## References
1. [Getting Physical with USB Type-C: Windows 10 RAM Forensics and UEFI Attacks - Alex Ionescu](http://publications.alex-ionescu.com/Recon/ReconBru%202017%20-%20Getting%20Physical%20with%20USB%20Type-C,%20Windows%2010%20RAM%20Forensics%20and%20UEFI%20Attacks.pdf)
2. [VmmWinInit_DTB_FindValidate_X64_LowStub](https://github.com/ufrisk/MemProcFS/blob/master/vmm/vmmwininit.c#L801)
3. [find_low_stub](https://github.com/chompie1337/SMBGhost_RCE_PoC/blob/master/exploit.py#L396)
4. [DriverInitPageTableBase](https://github.com/Cr4sh/KernelForge/blob/master/kforge_driver/kforge_driver.cpp#L60)
5. [WinIoQueryPML4Value](https://github.com/hfiref0x/WinObjEx64/blob/master/Source/WinObjEx64/drivers/winio.c#L188)