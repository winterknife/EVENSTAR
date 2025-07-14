# EVENSTAR - GetCurrentProcessorNumber

## Version
- `v1.0.0`

## Brief
- `ISA: x86`
- `Mode: Protected, Compatibility, Long`
- `Bitness: 32-bit, 64-bit`
- `CPL: 0, 3`
- `OS: Windows`
- `Language: C`
- Sample code that demonstrates the usage of the `RDPID`, `RDTSCP`, and the `LSL` instructions to fetch the current logical processor's ID

## Usage
```
C:\pub\bld>GetCurrentProcessorNumber.exe
[DBG]: [*] GetCurrentProcessorNumber Built Jul  6 2025 16:46:57
Press any key to continue . . .
[DBG]: [+] Logical processor count = 0n2
[DBG]: [+] Pinned all the threads of the current process to logical processor = 0n0
[DBG]: [+] Current logical processor's ID = 0n0
[DBG]: [+] Pinned all the threads of the current process to logical processor = 0n1
[DBG]: [+] Current logical processor's ID = 0n1
Press any key to continue . . .
```

## Tested OS Versions
- `Windows 11 21H2 Build 22000 Revision 675 64-bit`

## References
1. [Alex Ionescu’s Blog - Solution to Challenge](https://www.alex-ionescu.com/solution-to-challenge/)
2. [Processor Groups](https://learn.microsoft.com/en-us/windows/win32/procthread/processor-groups)
3. [GetCurrentProcessorNumber function (processthreadsapi.h)](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getcurrentprocessornumber)
4. [Multiple Processors](https://learn.microsoft.com/en-us/windows/win32/procthread/multiple-processors)
5. [On pinning and isolating CPU cores](https://manuel.bernhardt.io/posts/2023-11-16-core-pinning/)
6. [C++11 threads, affinity and hyperthreading](https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/)
7. [Intel® Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#ig_expand=5089,5263)