# EVENSTAR - ReadCRDbgExt

## Version
- `v10.0.6`

## Brief
- `ISA: x86`
- `Mode: Long`
- `Bitness: 64-bit`
- `CPL: 3`
- `OS: Windows`
- `Language: C`
- _WdbgExts_ "old style" debugger extension `DLL` to pretty print flags of various `CPU` `Control Registers (CR)`

## Usage
- Set up kernel-mode debugging of the target
```shell
0: kd> vertarget
Windows 10 Kernel Version 18362 MP (2 procs) Free x64
Edition build lab: 18362.1.amd64fre.19h1_release.190318-1202
Kernel base = 0xfffff807`2ea00000 PsLoadedModuleList = 0xfffff807`2ee461b0
Debug session time: Mon Oct 14 12:37:56.725 2024 (UTC - 4:00)
System Uptime: 0 days 0:18:20.646

0: kd> .load ReadCRDbgExt.dll

0: kd> !ReadCRDbgExt.help
Help for debugger extension DLL ReadCRDbgExt.dll
   help    - Show help menu
   readcr0 - Display CR0 flags
   readcr4 - Display CR4 flags

0: kd> !ReadCRDbgExt.readcr0
[!] Current processor number = 0
[+] CR0 = 0x80050033
    |-----|------|--------|
    | Bit | Flag | Status |
    |-----|------|--------|
    |   0 |   PE |      1 |
    |   1 |   MP |      1 |
    |   2 |   EM |      0 |
    |   3 |   TS |      0 |
    |   4 |   ET |      1 |
    |   5 |   NE |      1 |
    |  16 |   WP |      1 |
    |  18 |   AM |      1 |
    |  29 |   NW |      0 |
    |  30 |   CD |      0 |
    |  31 |   PG |      1 |
    |-----|------|--------|

0: kd> !ReadCRDbgExt.readcr4
[!] Current processor number = 0
[+] CR4 = 0x350EF8
    |-----|------------|--------|
    | Bit | Flag       | Status |
    |-----|------------|--------|
    |   0 |        VME |      0 |
    |   1 |        PVI |      0 |
    |   2 |        TSD |      0 |
    |   3 |         DE |      1 |
    |   4 |        PSE |      1 |
    |   5 |        PAE |      1 |
    |   6 |        MCE |      1 |
    |   7 |        PGE |      1 |
    |   8 |        PCE |      0 |
    |   9 |     OSFXSR |      1 |
    |  10 | OSXMMEXCPT |      1 |
    |  11 |       UMIP |      1 |
    |  12 |       LA57 |      0 |
    |  13 |       VMXE |      0 |
    |  14 |       SMXE |      0 |
    |  16 |   FSGSBASE |      1 |
    |  17 |      PCIDE |      0 |
    |  18 |    OSXSAVE |      1 |
    |  19 |         KL |      0 |
    |  20 |       SMEP |      1 |
    |  21 |       SMAP |      1 |
    |  22 |        PKE |      0 |
    |  23 |        CET |      0 |
    |  24 |        PKS |      0 |
    |  25 |      UINTR |      0 |
    |-----|------------|--------|

0: kd> .unload ReadCRDbgExt.dll
Unloading ReadCRDbgExt extension DLL
```

## Tested OS Versions
- `Windows 11 24H2 Build 26100 Revision 1882 64-bit`

## References
1. [Writing New Debugger Extensions](https://learn.microsoft.com/en-us/windows-hardware/drivers/debuggercmds/writing-new-debugger-extensions)
2. [simplext](https://github.com/tpn/winsdk-10/tree/master/Debuggers/x64/sdk/samples/simplext)
3. [Making WinDbg Your Friend - Creating Debugger Extensions](https://www.osronline.com/article.cfm%5Eid=52.htm)
4. [Writing Debugger Extensions](https://codemachine.com/presentations/GES2007.TRoy.Slides.pdf)