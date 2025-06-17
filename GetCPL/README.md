# EVENSTAR - GetCPL

## Version
- `v1.0.0`

## Brief
- `ISA: x86`
- `Mode: Real, Protected, Long`
- `Bitness: 16-bit, 32-bit, 64-bit`
- `CPL: 0, 3`
- `OS: Windows`
- `Language: C`
- Sample code that demonstrates the usage of the `SMSW` instruction to fetch the the `Machine Status Word` (bits 0 through 15 of control register `CR0`) and check the processor's `Current Privilege Level (CPL)` if the processor is running in `Protected` mode.

## Usage
- There aren't a lot of useful bits in the `MSW`
- One notable exception: `PE (Protection Enable)` bit (0)
- This flag enables Segmentation
- The processor maintains an internal state called `CPL` which is defined as the privilege level of the currently executing code
- `CPL` is used to determine whether certain operations are permitted or not
- `CPL` is given by `CS.RPL` (bits 0 and 1)
```shell
C:\pub\bld\DriverRun>GetCPL.exe
[*] GetCPL Built Jun 16 2025 18:13:39
Press any key to continue . . .
[DBG]: user-mode
Press any key to continue . . .

[DBG]: +++ GetCPL.sys Loaded +++
[DBG]: GetCPL.sys Built Jun 17 2025 07:12:51
[DBG]: GetCPL: DriverObject = FFFFC486721BDAF0
[DBG]: GetCPL: RegistryPath = \REGISTRY\MACHINE\SYSTEM\ControlSet001\Services\GetCPL
[DBG]: supervisor-mode
[DBG]: --- GetCPL.sys Unloaded ---
```

## Tested OS Versions
- `Windows 11 21H2 Build 22000 Revision 675 64-bit`

## References
1. [SMSW — Store Machine Status Word](https://namazso.github.io/x86/html/SMSW.html)
2. [The Segmented Memory Model and How It Works in Windows x64](https://antonioparata.blogspot.com/2023/01/the-segment-memory-model-and-how-it.html)