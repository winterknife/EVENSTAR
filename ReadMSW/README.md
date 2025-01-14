# EVENSTAR - ReadMSW

## Version
- `v1.0.0`

## Brief
- `ISA: x86`
- `Mode: Real, Protected, Long`
- `Bitness: 16-bit, 32-bit, 64-bit`
- `CPL: 0, 3`
- `OS: Windows`
- `Language: C`
- Sample code that demonstrates the usage of the `SMSW` instruction to fetch the the `Machine Status Word` (bits 0 through 15 of control register `CR0`) and check if the processor is running in `Protected` mode.

## Usage
- There aren't a lot of useful bits in the `MSW`
- One notable exception: `PE (Protection Enable)` bit (0)
- This flag enables Segmentation
- Under normal circumstances, the sample code will always inform that `CR0.PE` bit is set
- Only useful for low-level code such as `OS` and `Hypervisors`
- Another possible use might be for `VM` detection but more testing is needed
```shell
C:\Users\winterknife\Desktop\ACED\EVENSTAR\ReadMSW\Bin\x64>ReadMSW.exe
[*] ReadMSW Built Jan 14 2025 14:12:25
Press any key to continue . . .
Processor Execution Mode == Protected Mode
Press any key to continue . . .
```

## Tested OS Versions
- `Windows 11 24H2 Build 26100 Revision 1882 64-bit`

## References
1. [SMSW—Store Machine Status Word](https://namazso.github.io/x86/html/SMSW.html)