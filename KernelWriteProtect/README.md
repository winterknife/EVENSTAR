# EVENSTAR - KernelWriteProtect

## Version

- `v1.0.0`

## Brief

- `ISA: x86`
- `Mode: Long`
- `Bitness: 64-bit`
- `CPL: 0`
- `OS: Windows`
- `Language: C`
- Sample code that demonstrates two techniques for writing into read-only pages in kernel space using `CR0.WP` manipulation and `MDL` double mapping

## Usage

```
[DBG]: +++ KernelWriteProtect.sys Loaded +++
[DBG]: KernelWriteProtect.sys Built May 14 2026 18:20:42
[DBG]: KernelWriteProtect: DriverObject = FFFF808F23410E20
[DBG]: KernelWriteProtect: RegistryPath = \REGISTRY\MACHINE\SYSTEM\ControlSet001\Services\KernelWriteProtect
Break instruction exception - code 80000003 (first chance)
*******************************************************************************
*                                                                             *
*   You are seeing this message because you pressed either                    *
*       CTRL+C (if you run console kernel debugger) or,                       *
*       CTRL+BREAK (if you run GUI kernel debugger),                          *
*   on your debugger machine's keyboard.                                      *
*                                                                             *
*                   THIS IS NOT A BUG OR A SYSTEM CRASH                       *
*                                                                             *
* If you did not intend to break into the debugger, press the "g" key, then   *
* press the "Enter" key now.  This message might immediately reappear.  If it *
* does, press "g" and "Enter" again.                                          *
*                                                                             *
*******************************************************************************
nt!DbgBreakPointWithStatus:
fffff801`d1efb1b0 cc              int     3
0: kd> !pte 0xFFFFF78000000000
                                           VA fffff78000000000
PXE at FFFFEFF7FBFDFF78    PPE at FFFFEFF7FBFEF000    PDE at FFFFEFF7FDE00000    PTE at FFFFEFFBC0000000
contains 0000000000285063  contains 0000000000284063  contains 0000000000283063  contains 8A00000000282161
pfn 285       ---DA--KWEV  pfn 284       ---DA--KWEV  pfn 283       ---DA--KWEV  pfn 282       -G-DA--KR-V

0: kd> db 0xFFFFF78000000000 L8
fffff780`00000000  41 41 41 41 41 41 41 41                          AAAAAAAA
0: kd> g
[DBG]: --- KernelWriteProtect.sys Unloaded ---
```

## Tested OS Versions

- `Windows 11 25H2 Build 26200 Revision 8246 64-bit`

## References

1. [BattlEye hypervisor detection](https://secret.club/2020/01/12/battleye-hypervisor-detection.html)
2. [ac](https://github.com/donnaskiez/ac)
3. [EfiGuard](https://github.com/Mattiwatti/EfiGuard)
4. [kernelhook](https://github.com/adrianyy/kernelhook)