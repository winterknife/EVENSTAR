# EVENSTAR - KernelToUserInjector

## Version

- `v3.0.0`

## Brief

- `ISA: x86`
- `Mode: Long`
- `Bitness: 64-bit`
- `CPL: 0`
- `OS: Windows`
- `Language: C`
- Sample code that demonstrates code injection from kernel-mode into a user-land process using APCs

## Usage

```
[DBG]: +++ KernelToUserInjector.sys Loaded +++
[DBG]: KernelToUserInjector.sys Built May  6 2026 11:07:01
[DBG]: KernelToUserInjector: DriverObject = FFFFE508AFD7E2F0
[DBG]: KernelToUserInjector: RegistryPath = \REGISTRY\MACHINE\SYSTEM\ControlSet001\Services\KernelToUserInjector
[DBG]: [+] PID of target process: 712
[DBG]: [+] TID of thread in alertable wait state: 1032
[DBG]: [+] Payload buffer UVA: 0x0000020B242E0000
[DBG]: [+] Queued a special kernel APC to the target thread!
[DBG]: [+] Queued a regular user-mode APC to the target thread!
[DBG]: --- KernelToUserInjector.sys Unloaded ---
```

## Tested OS Versions

- `Windows 11 25H2 Build 26200 Revision 8246 64-bit`

## References

1. [APC Series: User APC Internals](https://repnz.github.io/posts/apc/kernel-user-apc-api/)
2. [Aspects of internals of the Asynchronous Procedure Calls from the kernel mode.](https://dennisbabkin.com/blog/?t=depths-of-windows-apc-aspects-of-asynchronous-procedure-call-internals-from-kernel-mode)
3. [Thread APC](http://uninformed.org/index.cgi?v=3&a=4&p=20)
4. [Bypassing the Microsoft-Windows-Threat-Intelligence Kernel APC Injection Sensor](https://medium.com/@philiptsukerman/bypassing-the-microsoft-windows-threat-intelligence-kernel-apc-injection-sensor-92266433e0b0)
5. [Blackbone](https://github.com/DarthTon/Blackbone)
6. [Circumventing Windows Defender ATP's user-mode APC Injection sensor from Kernel-mode](https://rce4fun.blogspot.com/2019/04/circumventing-windows-defender-atps.html)
7. [KernelInjector](https://github.com/0mWindyBug/KernelInjector)