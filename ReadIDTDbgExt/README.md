# EVENSTAR - ReadIDTDbgExt

## Version
- `v10.0.6`

## Brief
- `ISA: x86`
- `Mode: Long`
- `Bitness: 64-bit`
- `CPL: 3`
- `OS: Windows`
- `Language: C`
- _WdbgExts_ "old style" debugger extension `DLL` to pretty print all the gate descriptors in the `Interrupt Descriptor Table (IDT)`

## Usage
- Set up kernel-mode debugging of the target
```
0: kd> vertarget
Windows 10 Kernel Version 22000 MP (2 procs) Free x64
Product: WinNt, suite: TerminalServer SingleUserTS
Edition build lab: 22000.1.amd64fre.co_release.210604-1628
Kernel base = 0xfffff804`6580f000 PsLoadedModuleList = 0xfffff804`66438b90
Debug session time: Sun Jun 29 10:15:30.649 2025 (UTC - 4:00)
System Uptime: 0 days 1:21:59.548

0: kd> .load ReadIDTDbgExt.dll

0: kd> .chain
--snip--
Extension DLL chain:
    ReadIDTDbgExt: API 10.0.6, 
        [path: C:\Users\winterknife\Desktop\Tools\WinDbgExtensions\ReadIDTDbgExt.dll]
--snip--

0: kd> .extmatch /D /e ReadIDTDbgExt *
!ReadIDTDbgExt.help
!ReadIDTDbgExt.read_idt

0: kd> !ReadIDTDbgExt.help
Help for debugger extension DLL ReadIDTDbgExt.dll
   help     - Show help menu
   read_idt - Read and parse the gate descriptors in the Interrupt Descriptor Table (IDT)

0: kd> !ReadIDTDbgExt.read_idt
Connected to Windows 10 22000 x64 target at (Sun Jun 29 10:20:36.046 2025 (UTC - 4:00)), ptr64 TRUE
Loading Kernel Symbols
.............

Press ctrl-c (cdb, kd, ntsd) or ctrl-break (windbg) to abort symbol loads that take too long.
Run !sym noisy before .reload to track down problems loading symbols.

..................................................
................................................................
...................................
Loading User Symbols

Loading unloaded module list
........
[!] Current processor number = 0
[+] IDT Base Address=0xFFFFF80465083000
[+] IDT Limit=0xFFF
[+] nt!_KPCR KVA=0xFFFFF80464E8F000
[+] nt!_KPRCB KVA=0xFFFFF80464E8F180
[+] nt!_KPRCB.InterruptObject[0] KVA=0xFFFFF80464E92580
----------------------------------------------------------------------
[+] Vector Number: 0x0 (0n0)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C30E00 (nt!KiDivideErrorFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x1 (0n1)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C31100 (nt!KiDebugTrapOrFault)
[+] IST=0x4
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x2 (0n2)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C316C0 (nt!KiNmiInterrupt)
[+] IST=0x3
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x3 (0n3)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C31C00 (nt!KiBreakpointTrap)
[+] DPL=0x3
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x4 (0n4)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C31F40 (nt!KiOverflowTrap)
[+] DPL=0x3
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x5 (0n5)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C32240 (nt!KiBoundFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x6 (0n6)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C32780 (nt!KiInvalidOpcodeFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x7 (0n7)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C32C80 (nt!KiNpxNotAvailableFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x8 (0n8)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C33000 (nt!KiDoubleFaultAbort)
[+] IST=0x1
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x9 (0n9)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C33300 (nt!KiNpxSegmentOverrunAbort)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA (0n10)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C33640 (nt!KiInvalidTssFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB (0n11)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C33980 (nt!KiSegmentNotPresentFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC (0n12)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C33D40 (nt!KiStackFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD (0n13)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C34080 (nt!KiGeneralProtectionFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE (0n14)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C343C0 (nt!KiPageFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF (0n15)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C285E8 (nt!KiIsrThunk+0x78)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x10 (0n16)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C34A00 (nt!KiFloatingErrorFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x11 (0n17)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C34D80 (nt!KiAlignmentFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x12 (0n18)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C35080 (nt!KiMcheckAbort)
[+] IST=0x2
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x13 (0n19)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C35C40 (nt!KiXmmException)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x14 (0n20)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C36000 (nt!KiVirtualizationException)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x15 (0n21)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C36540 (nt!KiControlProtectionFault)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x16 (0n22)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28620 (nt!KiIsrThunk+0xB0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x17 (0n23)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28628 (nt!KiIsrThunk+0xB8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x18 (0n24)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28630 (nt!KiIsrThunk+0xC0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x19 (0n25)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28638 (nt!KiIsrThunk+0xC8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x1A (0n26)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28640 (nt!KiIsrThunk+0xD0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x1B (0n27)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28648 (nt!KiIsrThunk+0xD8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x1C (0n28)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28650 (nt!KiIsrThunk+0xE0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x1D (0n29)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28658 (nt!KiIsrThunk+0xE8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x1E (0n30)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28660 (nt!KiIsrThunk+0xF0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x1F (0n31)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C2A590 (nt!KiApcInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x20 (0n32)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C2C380 (nt!KiSwInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x21 (0n33)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28678 (nt!KiIsrThunk+0x108)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x22 (0n34)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28680 (nt!KiIsrThunk+0x110)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x23 (0n35)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28688 (nt!KiIsrThunk+0x118)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x24 (0n36)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28690 (nt!KiIsrThunk+0x120)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x25 (0n37)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28698 (nt!KiIsrThunk+0x128)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x26 (0n38)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C286A0 (nt!KiIsrThunk+0x130)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x27 (0n39)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C286A8 (nt!KiIsrThunk+0x138)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x28 (0n40)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C286B0 (nt!KiIsrThunk+0x140)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x29 (0n41)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C36AC0 (nt!KiRaiseSecurityCheckFailure)
[+] DPL=0x3
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x2A (0n42)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C286C0 (nt!KiIsrThunk+0x150)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x2B (0n43)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C286C8 (nt!KiIsrThunk+0x158)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x2C (0n44)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C36E00 (nt!KiRaiseAssertion)
[+] DPL=0x3
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x2D (0n45)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C37140 (nt!KiDebugServiceTrap)
[+] DPL=0x3
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x2E (0n46)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C286E0 (nt!KiIsrThunk+0x170)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x2F (0n47)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C2C9B0 (nt!KiDpcInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x30 (0n48)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C2AB90 (nt!KiHvInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x31 (0n49)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C2AEB0 (nt!KiVmbusInterrupt0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x32 (0n50)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C2B1D0 (nt!KiVmbusInterrupt1)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x33 (0n51)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C2B4F0 (nt!KiVmbusInterrupt2)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x34 (0n52)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C2B810 (nt!KiVmbusInterrupt3)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x35 (0n53)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465D2A670 (nt!HalpInterruptCmciService)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x36 (0n54)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465D2A670 (nt!HalpInterruptCmciService)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x37 (0n55)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28728 (nt!KiIsrThunk+0x1B8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x38 (0n56)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28730 (nt!KiIsrThunk+0x1C0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x39 (0n57)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28738 (nt!KiIsrThunk+0x1C8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x3A (0n58)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28740 (nt!KiIsrThunk+0x1D0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x3B (0n59)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28748 (nt!KiIsrThunk+0x1D8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x3C (0n60)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28750 (nt!KiIsrThunk+0x1E0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x3D (0n61)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28758 (nt!KiIsrThunk+0x1E8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x3E (0n62)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28760 (nt!KiIsrThunk+0x1F0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x3F (0n63)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28768 (nt!KiIsrThunk+0x1F8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x40 (0n64)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28770 (nt!KiIsrThunk+0x200)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x41 (0n65)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28778 (nt!KiIsrThunk+0x208)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x42 (0n66)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28780 (nt!KiIsrThunk+0x210)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x43 (0n67)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28788 (nt!KiIsrThunk+0x218)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x44 (0n68)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28790 (nt!KiIsrThunk+0x220)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x45 (0n69)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28798 (nt!KiIsrThunk+0x228)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x46 (0n70)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287A0 (nt!KiIsrThunk+0x230)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x47 (0n71)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287A8 (nt!KiIsrThunk+0x238)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x48 (0n72)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287B0 (nt!KiIsrThunk+0x240)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x49 (0n73)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287B8 (nt!KiIsrThunk+0x248)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x4A (0n74)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287C0 (nt!KiIsrThunk+0x250)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x4B (0n75)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287C8 (nt!KiIsrThunk+0x258)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x4C (0n76)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287D0 (nt!KiIsrThunk+0x260)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x4D (0n77)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287D8 (nt!KiIsrThunk+0x268)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x4E (0n78)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287E0 (nt!KiIsrThunk+0x270)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x4F (0n79)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C287E8 (nt!KiIsrThunk+0x278)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x50 (0n80)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x51 (0n81)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x52 (0n82)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x53 (0n83)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467510CA0 (storport!RaidpAdapterMSIInterruptRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x54 (0n84)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28810 (nt!KiIsrThunk+0x2A0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x55 (0n85)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28818 (nt!KiIsrThunk+0x2A8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x56 (0n86)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28820 (nt!KiIsrThunk+0x2B0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x57 (0n87)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28828 (nt!KiIsrThunk+0x2B8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x58 (0n88)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28830 (nt!KiIsrThunk+0x2C0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x59 (0n89)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28838 (nt!KiIsrThunk+0x2C8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x5A (0n90)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28840 (nt!KiIsrThunk+0x2D0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x5B (0n91)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28848 (nt!KiIsrThunk+0x2D8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x5C (0n92)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28850 (nt!KiIsrThunk+0x2E0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x5D (0n93)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28858 (nt!KiIsrThunk+0x2E8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x5E (0n94)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28860 (nt!KiIsrThunk+0x2F0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x5F (0n95)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28868 (nt!KiIsrThunk+0x2F8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x60 (0n96)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x61 (0n97)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x62 (0n98)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x63 (0n99)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467510CA0 (storport!RaidpAdapterMSIInterruptRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x64 (0n100)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28890 (nt!KiIsrThunk+0x320)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x65 (0n101)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28898 (nt!KiIsrThunk+0x328)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x66 (0n102)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288A0 (nt!KiIsrThunk+0x330)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x67 (0n103)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288A8 (nt!KiIsrThunk+0x338)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x68 (0n104)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288B0 (nt!KiIsrThunk+0x340)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x69 (0n105)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288B8 (nt!KiIsrThunk+0x348)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x6A (0n106)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288C0 (nt!KiIsrThunk+0x350)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x6B (0n107)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288C8 (nt!KiIsrThunk+0x358)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x6C (0n108)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288D0 (nt!KiIsrThunk+0x360)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x6D (0n109)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288D8 (nt!KiIsrThunk+0x368)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x6E (0n110)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288E0 (nt!KiIsrThunk+0x370)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x6F (0n111)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C288E8 (nt!KiIsrThunk+0x378)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x70 (0n112)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF806263744B0 (i8042prt!I8042MouseInterruptService)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x71 (0n113)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x72 (0n114)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x73 (0n115)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467510CA0 (storport!RaidpAdapterMSIInterruptRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x74 (0n116)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28910 (nt!KiIsrThunk+0x3A0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x75 (0n117)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28918 (nt!KiIsrThunk+0x3A8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x76 (0n118)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28920 (nt!KiIsrThunk+0x3B0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x77 (0n119)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28928 (nt!KiIsrThunk+0x3B8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x78 (0n120)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28930 (nt!KiIsrThunk+0x3C0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x79 (0n121)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28938 (nt!KiIsrThunk+0x3C8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x7A (0n122)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28940 (nt!KiIsrThunk+0x3D0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x7B (0n123)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28948 (nt!KiIsrThunk+0x3D8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x7C (0n124)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28950 (nt!KiIsrThunk+0x3E0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x7D (0n125)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28958 (nt!KiIsrThunk+0x3E8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x7E (0n126)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28960 (nt!KiIsrThunk+0x3F0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x7F (0n127)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28968 (nt!KiIsrThunk+0x3F8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x80 (0n128)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80626371660 (i8042prt!I8042KeyboardInterruptService)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x81 (0n129)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x82 (0n130)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
Unable to load image \SystemRoot\System32\drivers\vmci.sys, Win32 error 0n2
----------------------------------------------------------------------
[+] Vector Number: 0x83 (0n131)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF804674331C0 (vmci+0x31C0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x84 (0n132)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467A719D0 (ndis!ndisMiniportMessageIsr)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x85 (0n133)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28998 (nt!KiIsrThunk+0x428)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x86 (0n134)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289A0 (nt!KiIsrThunk+0x430)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x87 (0n135)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289A8 (nt!KiIsrThunk+0x438)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x88 (0n136)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289B0 (nt!KiIsrThunk+0x440)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x89 (0n137)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289B8 (nt!KiIsrThunk+0x448)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x8A (0n138)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289C0 (nt!KiIsrThunk+0x450)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x8B (0n139)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289C8 (nt!KiIsrThunk+0x458)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x8C (0n140)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289D0 (nt!KiIsrThunk+0x460)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x8D (0n141)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289D8 (nt!KiIsrThunk+0x468)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x8E (0n142)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289E0 (nt!KiIsrThunk+0x470)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x8F (0n143)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289E8 (nt!KiIsrThunk+0x478)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x90 (0n144)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C289F0 (nt!KiIsrThunk+0x480)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x91 (0n145)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x92 (0n146)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x93 (0n147)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF804674331C0 (vmci+0x31C0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x94 (0n148)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467A719D0 (ndis!ndisMiniportMessageIsr)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x95 (0n149)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A18 (nt!KiIsrThunk+0x4A8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x96 (0n150)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A20 (nt!KiIsrThunk+0x4B0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x97 (0n151)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A28 (nt!KiIsrThunk+0x4B8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x98 (0n152)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A30 (nt!KiIsrThunk+0x4C0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x99 (0n153)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A38 (nt!KiIsrThunk+0x4C8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x9A (0n154)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A40 (nt!KiIsrThunk+0x4D0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x9B (0n155)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A48 (nt!KiIsrThunk+0x4D8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x9C (0n156)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A50 (nt!KiIsrThunk+0x4E0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x9D (0n157)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A58 (nt!KiIsrThunk+0x4E8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x9E (0n158)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A60 (nt!KiIsrThunk+0x4F0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0x9F (0n159)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A68 (nt!KiIsrThunk+0x4F8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA0 (0n160)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A70 (nt!KiIsrThunk+0x500)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA1 (0n161)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA2 (0n162)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA3 (0n163)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF804674854D0 (ataport!IdePortInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA4 (0n164)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467A719D0 (ndis!ndisMiniportMessageIsr)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA5 (0n165)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28A98 (nt!KiIsrThunk+0x528)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA6 (0n166)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AA0 (nt!KiIsrThunk+0x530)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA7 (0n167)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AA8 (nt!KiIsrThunk+0x538)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA8 (0n168)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AB0 (nt!KiIsrThunk+0x540)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xA9 (0n169)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AB8 (nt!KiIsrThunk+0x548)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xAA (0n170)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AC0 (nt!KiIsrThunk+0x550)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xAB (0n171)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AC8 (nt!KiIsrThunk+0x558)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xAC (0n172)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AD0 (nt!KiIsrThunk+0x560)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xAD (0n173)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AD8 (nt!KiIsrThunk+0x568)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xAE (0n174)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AE0 (nt!KiIsrThunk+0x570)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xAF (0n175)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28AE8 (nt!KiIsrThunk+0x578)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB0 (0n176)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80466F97F40 (ACPI!ACPIInterruptServiceRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB1 (0n177)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB2 (0n178)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80467166710 (pci!ExpressRootPortMessageRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB3 (0n179)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF804674854D0 (ataport!IdePortInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB4 (0n180)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80626C30FE0 (dxgkrnl!DpiFdoLineInterruptRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB5 (0n181)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B18 (nt!KiIsrThunk+0x5A8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB6 (0n182)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B20 (nt!KiIsrThunk+0x5B0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB7 (0n183)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B28 (nt!KiIsrThunk+0x5B8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB8 (0n184)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B30 (nt!KiIsrThunk+0x5C0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xB9 (0n185)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B38 (nt!KiIsrThunk+0x5C8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xBA (0n186)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B40 (nt!KiIsrThunk+0x5D0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xBB (0n187)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B48 (nt!KiIsrThunk+0x5D8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xBC (0n188)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B50 (nt!KiIsrThunk+0x5E0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xBD (0n189)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B58 (nt!KiIsrThunk+0x5E8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xBE (0n190)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B60 (nt!KiIsrThunk+0x5F0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xBF (0n191)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B68 (nt!KiIsrThunk+0x5F8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC0 (0n192)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B70 (nt!KiIsrThunk+0x600)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC1 (0n193)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B78 (nt!KiIsrThunk+0x608)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC2 (0n194)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B80 (nt!KiIsrThunk+0x610)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC3 (0n195)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B88 (nt!KiIsrThunk+0x618)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC4 (0n196)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B90 (nt!KiIsrThunk+0x620)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC5 (0n197)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28B98 (nt!KiIsrThunk+0x628)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC6 (0n198)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BA0 (nt!KiIsrThunk+0x630)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC7 (0n199)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BA8 (nt!KiIsrThunk+0x638)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC8 (0n200)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BB0 (nt!KiIsrThunk+0x640)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xC9 (0n201)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BB8 (nt!KiIsrThunk+0x648)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xCA (0n202)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BC0 (nt!KiIsrThunk+0x650)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xCB (0n203)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BC8 (nt!KiIsrThunk+0x658)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xCC (0n204)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BD0 (nt!KiIsrThunk+0x660)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xCD (0n205)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BD8 (nt!KiIsrThunk+0x668)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xCE (0n206)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465D22C60 (nt!HalpIommuInterruptRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xCF (0n207)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BE8 (nt!KiIsrThunk+0x678)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD0 (0n208)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28BF0 (nt!KiIsrThunk+0x680)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD1 (0n209)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465A94C10 (nt!HalpTimerClockInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD2 (0n210)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465A96F70 (nt!HalpTimerClockIpiRoutine)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD3 (0n211)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C08 (nt!KiIsrThunk+0x698)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD4 (0n212)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C10 (nt!KiIsrThunk+0x6A0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD5 (0n213)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C18 (nt!KiIsrThunk+0x6A8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD6 (0n214)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C20 (nt!KiIsrThunk+0x6B0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD7 (0n215)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465D2A6B0 (nt!HalpInterruptRebootService)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD8 (0n216)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465D2A730 (nt!HalpInterruptStubService)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xD9 (0n217)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C38 (nt!KiIsrThunk+0x6C8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xDA (0n218)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C40 (nt!KiIsrThunk+0x6D0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xDB (0n219)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C48 (nt!KiIsrThunk+0x6D8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xDC (0n220)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C50 (nt!KiIsrThunk+0x6E0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xDD (0n221)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C58 (nt!KiIsrThunk+0x6E8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xDE (0n222)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C60 (nt!KiIsrThunk+0x6F0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xDF (0n223)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465D2A700 (nt!HalpInterruptSpuriousService)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE0 (0n224)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C70 (nt!KiIsrThunk+0x700)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE1 (0n225)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C2CF10 (nt!KiIpiInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE2 (0n226)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465BBFC10 (nt!HalpInterruptLocalErrorService)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE3 (0n227)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465D2A690 (nt!HalpInterruptDeferredRecoveryService)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE4 (0n228)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C90 (nt!KiIsrThunk+0x720)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE5 (0n229)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28C98 (nt!KiIsrThunk+0x728)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE6 (0n230)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CA0 (nt!KiIsrThunk+0x730)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE7 (0n231)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CA8 (nt!KiIsrThunk+0x738)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE8 (0n232)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CB0 (nt!KiIsrThunk+0x740)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xE9 (0n233)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CB8 (nt!KiIsrThunk+0x748)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xEA (0n234)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CC0 (nt!KiIsrThunk+0x750)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xEB (0n235)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CC8 (nt!KiIsrThunk+0x758)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xEC (0n236)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CD0 (nt!KiIsrThunk+0x760)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xED (0n237)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CD8 (nt!KiIsrThunk+0x768)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xEE (0n238)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CE0 (nt!KiIsrThunk+0x770)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xEF (0n239)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CE8 (nt!KiIsrThunk+0x778)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF0 (0n240)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CF0 (nt!KiIsrThunk+0x780)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF1 (0n241)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28CF8 (nt!KiIsrThunk+0x788)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF2 (0n242)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D00 (nt!KiIsrThunk+0x790)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF3 (0n243)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D08 (nt!KiIsrThunk+0x798)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF4 (0n244)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D10 (nt!KiIsrThunk+0x7A0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF5 (0n245)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D18 (nt!KiIsrThunk+0x7A8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF6 (0n246)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D20 (nt!KiIsrThunk+0x7B0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF7 (0n247)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D28 (nt!KiIsrThunk+0x7B8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF8 (0n248)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D30 (nt!KiIsrThunk+0x7C0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xF9 (0n249)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D38 (nt!KiIsrThunk+0x7C8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xFA (0n250)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D40 (nt!KiIsrThunk+0x7D0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xFB (0n251)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D48 (nt!KiIsrThunk+0x7D8)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xFC (0n252)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D50 (nt!KiIsrThunk+0x7E0)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xFD (0n253)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465D2CDB0 (nt!HalpTimerProfileInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xFE (0n254)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C5A9C0 (nt!HalpPerfInterrupt)
[+] DPL=0x0
----------------------------------------------------------------------
----------------------------------------------------------------------
[+] Vector Number: 0xFF (0n255)
[+] Type: Interrupt Gate
[+] Segment Selector=0x10
[+] ISR KVA=0xFFFFF80465C28D68 (nt!KiIsrThunk+0x7F8)
[+] DPL=0x0
----------------------------------------------------------------------

0: kd> .load SwishDbgExt.dll

0: kd> !ms_idt
    |-----|-----|--------------------|--------------------------------------------------------|---------|--------|
    | Cre | Idx | Address            | Name                                                   | Patched | Hooked |
    |-----|-----|--------------------|--------------------------------------------------------|---------|--------|
    |   0 |   0 | 0xFFFFF80465C30E00 | nt!KiDivideErrorFault                                  |         |        |
    |   0 |   1 | 0xFFFFF80465C31100 | nt!KiDebugTrapOrFault                                  |         |        |
    |   0 |   2 | 0xFFFFF80465C316C0 | nt!KiNmiInterrupt                                      |         |        |
    |   0 |   3 | 0xFFFFF80465C31C00 | nt!KiBreakpointTrap                                    |         |        |
    |   0 |   4 | 0xFFFFF80465C31F40 | nt!KiOverflowTrap                                      |         |        |
    |   0 |   5 | 0xFFFFF80465C32240 | nt!KiBoundFault                                        |         |        |
    |   0 |   6 | 0xFFFFF80465C32780 | nt!KiInvalidOpcodeFault                                |         |        |
    |   0 |   7 | 0xFFFFF80465C32C80 | nt!KiNpxNotAvailableFault                              |         |        |
    |   0 |   8 | 0xFFFFF80465C33000 | nt!KiDoubleFaultAbort                                  |         |        |
    |   0 |   9 | 0xFFFFF80465C33300 | nt!KiNpxSegmentOverrunAbort                            |         |        |
    |   0 |  10 | 0xFFFFF80465C33640 | nt!KiInvalidTssFault                                   |         |        |
    |   0 |  11 | 0xFFFFF80465C33980 | nt!KiSegmentNotPresentFault                            |         |        |
    |   0 |  12 | 0xFFFFF80465C33D40 | nt!KiStackFault                                        |         |        |
    |   0 |  13 | 0xFFFFF80465C34080 | nt!KiGeneralProtectionFault                            |         |        |
    |   0 |  14 | 0xFFFFF80465C343C0 | nt!KiPageFault                                         |         |        |
    |   0 |  15 | 0xFFFFF80465C285E8 | nt!KiIsrThunk+0x78                                     |         |        |
    |   0 |  16 | 0xFFFFF80465C34A00 | nt!KiFloatingErrorFault                                |         |        |
    |   0 |  17 | 0xFFFFF80465C34D80 | nt!KiAlignmentFault                                    |         |        |
    |   0 |  18 | 0xFFFFF80465C35080 | nt!KiMcheckAbort                                       |         |        |
    |   0 |  19 | 0xFFFFF80465C35C40 | nt!KiXmmException                                      |         |        |
    |   0 |  20 | 0xFFFFF80465C36000 | nt!KiVirtualizationException                           |         |        |
    |   0 |  21 | 0xFFFFF80465C36540 | nt!KiControlProtectionFault                            |         |        |
    |   0 |  22 | 0xFFFFF80465C28620 | nt!KiIsrThunk+0xb0                                     |         |        |
    |   0 |  23 | 0xFFFFF80465C28628 | nt!KiIsrThunk+0xb8                                     |         |        |
    |   0 |  24 | 0xFFFFF80465C28630 | nt!KiIsrThunk+0xc0                                     |         |        |
    |   0 |  25 | 0xFFFFF80465C28638 | nt!KiIsrThunk+0xc8                                     |         |        |
    |   0 |  26 | 0xFFFFF80465C28640 | nt!KiIsrThunk+0xd0                                     |         |        |
    |   0 |  27 | 0xFFFFF80465C28648 | nt!KiIsrThunk+0xd8                                     |         |        |
    |   0 |  28 | 0xFFFFF80465C28650 | nt!KiIsrThunk+0xe0                                     |         |        |
    |   0 |  29 | 0xFFFFF80465C28658 | nt!KiIsrThunk+0xe8                                     |         |        |
    |   0 |  30 | 0xFFFFF80465C28660 | nt!KiIsrThunk+0xf0                                     |         |        |
    |   0 |  31 | 0xFFFFF80465C2A590 | nt!KiApcInterrupt                                      |         |        |
    |   0 |  32 | 0xFFFFF80465C2C380 | nt!KiSwInterrupt                                       |         |        |
    |   0 |  33 | 0xFFFFF80465C28678 | nt!KiIsrThunk+0x108                                    |         |        |
    |   0 |  34 | 0xFFFFF80465C28680 | nt!KiIsrThunk+0x110                                    |         |        |
    |   0 |  35 | 0xFFFFF80465C28688 | nt!KiIsrThunk+0x118                                    |         |        |
    |   0 |  36 | 0xFFFFF80465C28690 | nt!KiIsrThunk+0x120                                    |         |        |
    |   0 |  37 | 0xFFFFF80465C28698 | nt!KiIsrThunk+0x128                                    |         |        |
    |   0 |  38 | 0xFFFFF80465C286A0 | nt!KiIsrThunk+0x130                                    |         |        |
    |   0 |  39 | 0xFFFFF80465C286A8 | nt!KiIsrThunk+0x138                                    |         |        |
    |   0 |  40 | 0xFFFFF80465C286B0 | nt!KiIsrThunk+0x140                                    |         |        |
    |   0 |  41 | 0xFFFFF80465C36AC0 | nt!KiRaiseSecurityCheckFailure                         |         |        |
    |   0 |  42 | 0xFFFFF80465C286C0 | nt!KiIsrThunk+0x150                                    |         |        |
    |   0 |  43 | 0xFFFFF80465C286C8 | nt!KiIsrThunk+0x158                                    |         |        |
    |   0 |  44 | 0xFFFFF80465C36E00 | nt!KiRaiseAssertion                                    |         |        |
    |   0 |  45 | 0xFFFFF80465C37140 | nt!KiDebugServiceTrap                                  |         |        |
    |   0 |  46 | 0xFFFFF80465C286E0 | nt!KiIsrThunk+0x170                                    |         |        |
    |   0 |  47 | 0xFFFFF80465C2C9B0 | nt!KiDpcInterrupt                                      |         |        |
    |   0 |  48 | 0xFFFFF80465C2AB90 | nt!KiHvInterrupt                                       |         |        |
    |   0 |  49 | 0xFFFFF80465C2AEB0 | nt!KiVmbusInterrupt0                                   |         |        |
    |   0 |  50 | 0xFFFFF80465C2B1D0 | nt!KiVmbusInterrupt1                                   |         |        |
    |   0 |  51 | 0xFFFFF80465C2B4F0 | nt!KiVmbusInterrupt2                                   |         |        |
    |   0 |  52 | 0xFFFFF80465C2B810 | nt!KiVmbusInterrupt3                                   |         |        |
    |   0 |  53 | 0xFFFFF80465D2A670 | nt!HalpInterruptCmciService                            |         |        |
    |   0 |  54 | 0xFFFFF80465D2A670 | nt!HalpInterruptCmciService                            |         |        |
    |   0 |  55 | 0xFFFFF80465C28728 | nt!KiIsrThunk+0x1b8                                    |         |        |
    |   0 |  56 | 0xFFFFF80465C28730 | nt!KiIsrThunk+0x1c0                                    |         |        |
    |   0 |  57 | 0xFFFFF80465C28738 | nt!KiIsrThunk+0x1c8                                    |         |        |
    |   0 |  58 | 0xFFFFF80465C28740 | nt!KiIsrThunk+0x1d0                                    |         |        |
    |   0 |  59 | 0xFFFFF80465C28748 | nt!KiIsrThunk+0x1d8                                    |         |        |
    |   0 |  60 | 0xFFFFF80465C28750 | nt!KiIsrThunk+0x1e0                                    |         |        |
    |   0 |  61 | 0xFFFFF80465C28758 | nt!KiIsrThunk+0x1e8                                    |         |        |
    |   0 |  62 | 0xFFFFF80465C28760 | nt!KiIsrThunk+0x1f0                                    |         |        |
    |   0 |  63 | 0xFFFFF80465C28768 | nt!KiIsrThunk+0x1f8                                    |         |        |
    |   0 |  64 | 0xFFFFF80465C28770 | nt!KiIsrThunk+0x200                                    |         |        |
    |   0 |  65 | 0xFFFFF80465C28778 | nt!KiIsrThunk+0x208                                    |         |        |
    |   0 |  66 | 0xFFFFF80465C28780 | nt!KiIsrThunk+0x210                                    |         |        |
    |   0 |  67 | 0xFFFFF80465C28788 | nt!KiIsrThunk+0x218                                    |         |        |
    |   0 |  68 | 0xFFFFF80465C28790 | nt!KiIsrThunk+0x220                                    |         |        |
    |   0 |  69 | 0xFFFFF80465C28798 | nt!KiIsrThunk+0x228                                    |         |        |
    |   0 |  70 | 0xFFFFF80465C287A0 | nt!KiIsrThunk+0x230                                    |         |        |
    |   0 |  71 | 0xFFFFF80465C287A8 | nt!KiIsrThunk+0x238                                    |         |        |
    |   0 |  72 | 0xFFFFF80465C287B0 | nt!KiIsrThunk+0x240                                    |         |        |
    |   0 |  73 | 0xFFFFF80465C287B8 | nt!KiIsrThunk+0x248                                    |         |        |
    |   0 |  74 | 0xFFFFF80465C287C0 | nt!KiIsrThunk+0x250                                    |         |        |
    |   0 |  75 | 0xFFFFF80465C287C8 | nt!KiIsrThunk+0x258                                    |         |        |
    |   0 |  76 | 0xFFFFF80465C287D0 | nt!KiIsrThunk+0x260                                    |         |        |
    |   0 |  77 | 0xFFFFF80465C287D8 | nt!KiIsrThunk+0x268                                    |         |        |
    |   0 |  78 | 0xFFFFF80465C287E0 | nt!KiIsrThunk+0x270                                    |         |        |
    |   0 |  79 | 0xFFFFF80465C287E8 | nt!KiIsrThunk+0x278                                    |         |        |
    |   0 |  80 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 |  81 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 |  82 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 |  83 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 |  84 | 0xFFFFF80465C28810 | nt!KiIsrThunk+0x2a0                                    |         |        |
    |   0 |  85 | 0xFFFFF80465C28818 | nt!KiIsrThunk+0x2a8                                    |         |        |
    |   0 |  86 | 0xFFFFF80465C28820 | nt!KiIsrThunk+0x2b0                                    |         |        |
    |   0 |  87 | 0xFFFFF80465C28828 | nt!KiIsrThunk+0x2b8                                    |         |        |
    |   0 |  88 | 0xFFFFF80465C28830 | nt!KiIsrThunk+0x2c0                                    |         |        |
    |   0 |  89 | 0xFFFFF80465C28838 | nt!KiIsrThunk+0x2c8                                    |         |        |
    |   0 |  90 | 0xFFFFF80465C28840 | nt!KiIsrThunk+0x2d0                                    |         |        |
    |   0 |  91 | 0xFFFFF80465C28848 | nt!KiIsrThunk+0x2d8                                    |         |        |
    |   0 |  92 | 0xFFFFF80465C28850 | nt!KiIsrThunk+0x2e0                                    |         |        |
    |   0 |  93 | 0xFFFFF80465C28858 | nt!KiIsrThunk+0x2e8                                    |         |        |
    |   0 |  94 | 0xFFFFF80465C28860 | nt!KiIsrThunk+0x2f0                                    |         |        |
    |   0 |  95 | 0xFFFFF80465C28868 | nt!KiIsrThunk+0x2f8                                    |         |        |
    |   0 |  96 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 |  97 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 |  98 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 |  99 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 100 | 0xFFFFF80465C28890 | nt!KiIsrThunk+0x320                                    |         |        |
    |   0 | 101 | 0xFFFFF80465C28898 | nt!KiIsrThunk+0x328                                    |         |        |
    |   0 | 102 | 0xFFFFF80465C288A0 | nt!KiIsrThunk+0x330                                    |         |        |
    |   0 | 103 | 0xFFFFF80465C288A8 | nt!KiIsrThunk+0x338                                    |         |        |
    |   0 | 104 | 0xFFFFF80465C288B0 | nt!KiIsrThunk+0x340                                    |         |        |
    |   0 | 105 | 0xFFFFF80465C288B8 | nt!KiIsrThunk+0x348                                    |         |        |
    |   0 | 106 | 0xFFFFF80465C288C0 | nt!KiIsrThunk+0x350                                    |         |        |
    |   0 | 107 | 0xFFFFF80465C288C8 | nt!KiIsrThunk+0x358                                    |         |        |
    |   0 | 108 | 0xFFFFF80465C288D0 | nt!KiIsrThunk+0x360                                    |         |        |
    |   0 | 109 | 0xFFFFF80465C288D8 | nt!KiIsrThunk+0x368                                    |         |        |
    |   0 | 110 | 0xFFFFF80465C288E0 | nt!KiIsrThunk+0x370                                    |         |        |
    |   0 | 111 | 0xFFFFF80465C288E8 | nt!KiIsrThunk+0x378                                    |         |        |
    |   0 | 112 | 0xFFFFF806263744B0 | i8042prt!I8042MouseInterruptService                    |         |        |
    |   0 | 113 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 114 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 115 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 116 | 0xFFFFF80465C28910 | nt!KiIsrThunk+0x3a0                                    |         |        |
    |   0 | 117 | 0xFFFFF80465C28918 | nt!KiIsrThunk+0x3a8                                    |         |        |
    |   0 | 118 | 0xFFFFF80465C28920 | nt!KiIsrThunk+0x3b0                                    |         |        |
    |   0 | 119 | 0xFFFFF80465C28928 | nt!KiIsrThunk+0x3b8                                    |         |        |
    |   0 | 120 | 0xFFFFF80465C28930 | nt!KiIsrThunk+0x3c0                                    |         |        |
    |   0 | 121 | 0xFFFFF80465C28938 | nt!KiIsrThunk+0x3c8                                    |         |        |
    |   0 | 122 | 0xFFFFF80465C28940 | nt!KiIsrThunk+0x3d0                                    |         |        |
    |   0 | 123 | 0xFFFFF80465C28948 | nt!KiIsrThunk+0x3d8                                    |         |        |
    |   0 | 124 | 0xFFFFF80465C28950 | nt!KiIsrThunk+0x3e0                                    |         |        |
    |   0 | 125 | 0xFFFFF80465C28958 | nt!KiIsrThunk+0x3e8                                    |         |        |
    |   0 | 126 | 0xFFFFF80465C28960 | nt!KiIsrThunk+0x3f0                                    |         |        |
    |   0 | 127 | 0xFFFFF80465C28968 | nt!KiIsrThunk+0x3f8                                    |         |        |
    |   0 | 128 | 0xFFFFF80626371660 | i8042prt!I8042KeyboardInterruptService                 |         |        |
    |   0 | 129 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 130 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 131 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 132 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 133 | 0xFFFFF80465C28998 | nt!KiIsrThunk+0x428                                    |         |        |
    |   0 | 134 | 0xFFFFF80465C289A0 | nt!KiIsrThunk+0x430                                    |         |        |
    |   0 | 135 | 0xFFFFF80465C289A8 | nt!KiIsrThunk+0x438                                    |         |        |
    |   0 | 136 | 0xFFFFF80465C289B0 | nt!KiIsrThunk+0x440                                    |         |        |
    |   0 | 137 | 0xFFFFF80465C289B8 | nt!KiIsrThunk+0x448                                    |         |        |
    |   0 | 138 | 0xFFFFF80465C289C0 | nt!KiIsrThunk+0x450                                    |         |        |
    |   0 | 139 | 0xFFFFF80465C289C8 | nt!KiIsrThunk+0x458                                    |         |        |
    |   0 | 140 | 0xFFFFF80465C289D0 | nt!KiIsrThunk+0x460                                    |         |        |
    |   0 | 141 | 0xFFFFF80465C289D8 | nt!KiIsrThunk+0x468                                    |         |        |
    |   0 | 142 | 0xFFFFF80465C289E0 | nt!KiIsrThunk+0x470                                    |         |        |
    |   0 | 143 | 0xFFFFF80465C289E8 | nt!KiIsrThunk+0x478                                    |         |        |
    |   0 | 144 | 0xFFFFF80465C289F0 | nt!KiIsrThunk+0x480                                    |         |        |
    |   0 | 145 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 146 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 147 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 148 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 149 | 0xFFFFF80465C28A18 | nt!KiIsrThunk+0x4a8                                    |         |        |
    |   0 | 150 | 0xFFFFF80465C28A20 | nt!KiIsrThunk+0x4b0                                    |         |        |
    |   0 | 151 | 0xFFFFF80465C28A28 | nt!KiIsrThunk+0x4b8                                    |         |        |
    |   0 | 152 | 0xFFFFF80465C28A30 | nt!KiIsrThunk+0x4c0                                    |         |        |
    |   0 | 153 | 0xFFFFF80465C28A38 | nt!KiIsrThunk+0x4c8                                    |         |        |
    |   0 | 154 | 0xFFFFF80465C28A40 | nt!KiIsrThunk+0x4d0                                    |         |        |
    |   0 | 155 | 0xFFFFF80465C28A48 | nt!KiIsrThunk+0x4d8                                    |         |        |
    |   0 | 156 | 0xFFFFF80465C28A50 | nt!KiIsrThunk+0x4e0                                    |         |        |
    |   0 | 157 | 0xFFFFF80465C28A58 | nt!KiIsrThunk+0x4e8                                    |         |        |
    |   0 | 158 | 0xFFFFF80465C28A60 | nt!KiIsrThunk+0x4f0                                    |         |        |
    |   0 | 159 | 0xFFFFF80465C28A68 | nt!KiIsrThunk+0x4f8                                    |         |        |
    |   0 | 160 | 0xFFFFF80465C28A70 | nt!KiIsrThunk+0x500                                    |         |        |
    |   0 | 161 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 162 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 163 | 0xFFFFF804674854D0 | ataport!IdePortInterrupt                               |         |        |
    |   0 | 164 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 165 | 0xFFFFF80465C28A98 | nt!KiIsrThunk+0x528                                    |         |        |
    |   0 | 166 | 0xFFFFF80465C28AA0 | nt!KiIsrThunk+0x530                                    |         |        |
    |   0 | 167 | 0xFFFFF80465C28AA8 | nt!KiIsrThunk+0x538                                    |         |        |
    |   0 | 168 | 0xFFFFF80465C28AB0 | nt!KiIsrThunk+0x540                                    |         |        |
    |   0 | 169 | 0xFFFFF80465C28AB8 | nt!KiIsrThunk+0x548                                    |         |        |
    |   0 | 170 | 0xFFFFF80465C28AC0 | nt!KiIsrThunk+0x550                                    |         |        |
    |   0 | 171 | 0xFFFFF80465C28AC8 | nt!KiIsrThunk+0x558                                    |         |        |
    |   0 | 172 | 0xFFFFF80465C28AD0 | nt!KiIsrThunk+0x560                                    |         |        |
    |   0 | 173 | 0xFFFFF80465C28AD8 | nt!KiIsrThunk+0x568                                    |         |        |
    |   0 | 174 | 0xFFFFF80465C28AE0 | nt!KiIsrThunk+0x570                                    |         |        |
    |   0 | 175 | 0xFFFFF80465C28AE8 | nt!KiIsrThunk+0x578                                    |         |        |
    |   0 | 176 | 0xFFFFF80466F97F40 | ACPI!ACPIInterruptServiceRoutine                       |         |        |
    |   0 | 177 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 178 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   0 | 179 | 0xFFFFF804674854D0 | ataport!IdePortInterrupt                               |         |        |
    |   0 | 180 | 0xFFFFF80626C30FE0 | dxgkrnl!DpiFdoLineInterruptRoutine                     |         |        |
    |   0 | 181 | 0xFFFFF80465C28B18 | nt!KiIsrThunk+0x5a8                                    |         |        |
    |   0 | 182 | 0xFFFFF80465C28B20 | nt!KiIsrThunk+0x5b0                                    |         |        |
    |   0 | 183 | 0xFFFFF80465C28B28 | nt!KiIsrThunk+0x5b8                                    |         |        |
    |   0 | 184 | 0xFFFFF80465C28B30 | nt!KiIsrThunk+0x5c0                                    |         |        |
    |   0 | 185 | 0xFFFFF80465C28B38 | nt!KiIsrThunk+0x5c8                                    |         |        |
    |   0 | 186 | 0xFFFFF80465C28B40 | nt!KiIsrThunk+0x5d0                                    |         |        |
    |   0 | 187 | 0xFFFFF80465C28B48 | nt!KiIsrThunk+0x5d8                                    |         |        |
    |   0 | 188 | 0xFFFFF80465C28B50 | nt!KiIsrThunk+0x5e0                                    |         |        |
    |   0 | 189 | 0xFFFFF80465C28B58 | nt!KiIsrThunk+0x5e8                                    |         |        |
    |   0 | 190 | 0xFFFFF80465C28B60 | nt!KiIsrThunk+0x5f0                                    |         |        |
    |   0 | 191 | 0xFFFFF80465C28B68 | nt!KiIsrThunk+0x5f8                                    |         |        |
    |   0 | 192 | 0xFFFFF80465C28B70 | nt!KiIsrThunk+0x600                                    |         |        |
    |   0 | 193 | 0xFFFFF80465C28B78 | nt!KiIsrThunk+0x608                                    |         |        |
    |   0 | 194 | 0xFFFFF80465C28B80 | nt!KiIsrThunk+0x610                                    |         |        |
    |   0 | 195 | 0xFFFFF80465C28B88 | nt!KiIsrThunk+0x618                                    |         |        |
    |   0 | 196 | 0xFFFFF80465C28B90 | nt!KiIsrThunk+0x620                                    |         |        |
    |   0 | 197 | 0xFFFFF80465C28B98 | nt!KiIsrThunk+0x628                                    |         |        |
    |   0 | 198 | 0xFFFFF80465C28BA0 | nt!KiIsrThunk+0x630                                    |         |        |
    |   0 | 199 | 0xFFFFF80465C28BA8 | nt!KiIsrThunk+0x638                                    |         |        |
    |   0 | 200 | 0xFFFFF80465C28BB0 | nt!KiIsrThunk+0x640                                    |         |        |
    |   0 | 201 | 0xFFFFF80465C28BB8 | nt!KiIsrThunk+0x648                                    |         |        |
    |   0 | 202 | 0xFFFFF80465C28BC0 | nt!KiIsrThunk+0x650                                    |         |        |
    |   0 | 203 | 0xFFFFF80465C28BC8 | nt!KiIsrThunk+0x658                                    |         |        |
    |   0 | 204 | 0xFFFFF80465C28BD0 | nt!KiIsrThunk+0x660                                    |         |        |
    |   0 | 205 | 0xFFFFF80465C28BD8 | nt!KiIsrThunk+0x668                                    |         |        |
    |   0 | 206 | 0xFFFFF80465D22C60 | nt!HalpIommuInterruptRoutine                           |         |        |
    |   0 | 207 | 0xFFFFF80465C28BE8 | nt!KiIsrThunk+0x678                                    |         |        |
    |   0 | 208 | 0xFFFFF80465C28BF0 | nt!KiIsrThunk+0x680                                    |         |        |
    |   0 | 209 | 0xFFFFF80465A94C10 | nt!HalpTimerClockInterrupt                             |         |        |
    |   0 | 210 | 0xFFFFF80465A96F70 | nt!HalpTimerClockIpiRoutine                            |         |        |
    |   0 | 211 | 0xFFFFF80465C28C08 | nt!KiIsrThunk+0x698                                    |         |        |
    |   0 | 212 | 0xFFFFF80465C28C10 | nt!KiIsrThunk+0x6a0                                    |         |        |
    |   0 | 213 | 0xFFFFF80465C28C18 | nt!KiIsrThunk+0x6a8                                    |         |        |
    |   0 | 214 | 0xFFFFF80465C28C20 | nt!KiIsrThunk+0x6b0                                    |         |        |
    |   0 | 215 | 0xFFFFF80465D2A6B0 | nt!HalpInterruptRebootService                          |         |        |
    |   0 | 216 | 0xFFFFF80465D2A730 | nt!HalpInterruptStubService                            |         |        |
    |   0 | 217 | 0xFFFFF80465C28C38 | nt!KiIsrThunk+0x6c8                                    |         |        |
    |   0 | 218 | 0xFFFFF80465C28C40 | nt!KiIsrThunk+0x6d0                                    |         |        |
    |   0 | 219 | 0xFFFFF80465C28C48 | nt!KiIsrThunk+0x6d8                                    |         |        |
    |   0 | 220 | 0xFFFFF80465C28C50 | nt!KiIsrThunk+0x6e0                                    |         |        |
    |   0 | 221 | 0xFFFFF80465C28C58 | nt!KiIsrThunk+0x6e8                                    |         |        |
    |   0 | 222 | 0xFFFFF80465C28C60 | nt!KiIsrThunk+0x6f0                                    |         |        |
    |   0 | 223 | 0xFFFFF80465D2A700 | nt!HalpInterruptSpuriousService                        |         |        |
    |   0 | 224 | 0xFFFFF80465C28C70 | nt!KiIsrThunk+0x700                                    |         |        |
    |   0 | 225 | 0xFFFFF80465C2CF10 | nt!KiIpiInterrupt                                      |         |        |
    |   0 | 226 | 0xFFFFF80465BBFC10 | nt!HalpInterruptLocalErrorService                      |         |        |
    |   0 | 227 | 0xFFFFF80465D2A690 | nt!HalpInterruptDeferredRecoveryService                |         |        |
    |   0 | 228 | 0xFFFFF80465C28C90 | nt!KiIsrThunk+0x720                                    |         |        |
    |   0 | 229 | 0xFFFFF80465C28C98 | nt!KiIsrThunk+0x728                                    |         |        |
    |   0 | 230 | 0xFFFFF80465C28CA0 | nt!KiIsrThunk+0x730                                    |         |        |
    |   0 | 231 | 0xFFFFF80465C28CA8 | nt!KiIsrThunk+0x738                                    |         |        |
    |   0 | 232 | 0xFFFFF80465C28CB0 | nt!KiIsrThunk+0x740                                    |         |        |
    |   0 | 233 | 0xFFFFF80465C28CB8 | nt!KiIsrThunk+0x748                                    |         |        |
    |   0 | 234 | 0xFFFFF80465C28CC0 | nt!KiIsrThunk+0x750                                    |         |        |
    |   0 | 235 | 0xFFFFF80465C28CC8 | nt!KiIsrThunk+0x758                                    |         |        |
    |   0 | 236 | 0xFFFFF80465C28CD0 | nt!KiIsrThunk+0x760                                    |         |        |
    |   0 | 237 | 0xFFFFF80465C28CD8 | nt!KiIsrThunk+0x768                                    |         |        |
    |   0 | 238 | 0xFFFFF80465C28CE0 | nt!KiIsrThunk+0x770                                    |         |        |
    |   0 | 239 | 0xFFFFF80465C28CE8 | nt!KiIsrThunk+0x778                                    |         |        |
    |   0 | 240 | 0xFFFFF80465C28CF0 | nt!KiIsrThunk+0x780                                    |         |        |
    |   0 | 241 | 0xFFFFF80465C28CF8 | nt!KiIsrThunk+0x788                                    |         |        |
    |   0 | 242 | 0xFFFFF80465C28D00 | nt!KiIsrThunk+0x790                                    |         |        |
    |   0 | 243 | 0xFFFFF80465C28D08 | nt!KiIsrThunk+0x798                                    |         |        |
    |   0 | 244 | 0xFFFFF80465C28D10 | nt!KiIsrThunk+0x7a0                                    |         |        |
    |   0 | 245 | 0xFFFFF80465C28D18 | nt!KiIsrThunk+0x7a8                                    |         |        |
    |   0 | 246 | 0xFFFFF80465C28D20 | nt!KiIsrThunk+0x7b0                                    |         |        |
    |   0 | 247 | 0xFFFFF80465C28D28 | nt!KiIsrThunk+0x7b8                                    |         |        |
    |   0 | 248 | 0xFFFFF80465C28D30 | nt!KiIsrThunk+0x7c0                                    |         |        |
    |   0 | 249 | 0xFFFFF80465C28D38 | nt!KiIsrThunk+0x7c8                                    |         |        |
    |   0 | 250 | 0xFFFFF80465C28D40 | nt!KiIsrThunk+0x7d0                                    |         |        |
    |   0 | 251 | 0xFFFFF80465C28D48 | nt!KiIsrThunk+0x7d8                                    |         |        |
    |   0 | 252 | 0xFFFFF80465C28D50 | nt!KiIsrThunk+0x7e0                                    |         |        |
    |   0 | 253 | 0xFFFFF80465D2CDB0 | nt!HalpTimerProfileInterrupt                           |         |        |
    |   0 | 254 | 0xFFFFF80465C5A9C0 | nt!HalpPerfInterrupt                                   |         |        |
    |   0 | 255 | 0xFFFFF80465C28D68 | nt!KiIsrThunk+0x7f8                                    |         |        |
    |   1 |   0 | 0xFFFFF80465C30E00 | nt!KiDivideErrorFault                                  |         |        |
    |   1 |   1 | 0xFFFFF80465C31100 | nt!KiDebugTrapOrFault                                  |         |        |
    |   1 |   2 | 0xFFFFF80465C316C0 | nt!KiNmiInterrupt                                      |         |        |
    |   1 |   3 | 0xFFFFF80465C31C00 | nt!KiBreakpointTrap                                    |         |        |
    |   1 |   4 | 0xFFFFF80465C31F40 | nt!KiOverflowTrap                                      |         |        |
    |   1 |   5 | 0xFFFFF80465C32240 | nt!KiBoundFault                                        |         |        |
    |   1 |   6 | 0xFFFFF80465C32780 | nt!KiInvalidOpcodeFault                                |         |        |
    |   1 |   7 | 0xFFFFF80465C32C80 | nt!KiNpxNotAvailableFault                              |         |        |
    |   1 |   8 | 0xFFFFF80465C33000 | nt!KiDoubleFaultAbort                                  |         |        |
    |   1 |   9 | 0xFFFFF80465C33300 | nt!KiNpxSegmentOverrunAbort                            |         |        |
    |   1 |  10 | 0xFFFFF80465C33640 | nt!KiInvalidTssFault                                   |         |        |
    |   1 |  11 | 0xFFFFF80465C33980 | nt!KiSegmentNotPresentFault                            |         |        |
    |   1 |  12 | 0xFFFFF80465C33D40 | nt!KiStackFault                                        |         |        |
    |   1 |  13 | 0xFFFFF80465C34080 | nt!KiGeneralProtectionFault                            |         |        |
    |   1 |  14 | 0xFFFFF80465C343C0 | nt!KiPageFault                                         |         |        |
    |   1 |  15 | 0xFFFFF80465C285E8 | nt!KiIsrThunk+0x78                                     |         |        |
    |   1 |  16 | 0xFFFFF80465C34A00 | nt!KiFloatingErrorFault                                |         |        |
    |   1 |  17 | 0xFFFFF80465C34D80 | nt!KiAlignmentFault                                    |         |        |
    |   1 |  18 | 0xFFFFF80465C35080 | nt!KiMcheckAbort                                       |         |        |
    |   1 |  19 | 0xFFFFF80465C35C40 | nt!KiXmmException                                      |         |        |
    |   1 |  20 | 0xFFFFF80465C36000 | nt!KiVirtualizationException                           |         |        |
    |   1 |  21 | 0xFFFFF80465C36540 | nt!KiControlProtectionFault                            |         |        |
    |   1 |  22 | 0xFFFFF80465C28620 | nt!KiIsrThunk+0xb0                                     |         |        |
    |   1 |  23 | 0xFFFFF80465C28628 | nt!KiIsrThunk+0xb8                                     |         |        |
    |   1 |  24 | 0xFFFFF80465C28630 | nt!KiIsrThunk+0xc0                                     |         |        |
    |   1 |  25 | 0xFFFFF80465C28638 | nt!KiIsrThunk+0xc8                                     |         |        |
    |   1 |  26 | 0xFFFFF80465C28640 | nt!KiIsrThunk+0xd0                                     |         |        |
    |   1 |  27 | 0xFFFFF80465C28648 | nt!KiIsrThunk+0xd8                                     |         |        |
    |   1 |  28 | 0xFFFFF80465C28650 | nt!KiIsrThunk+0xe0                                     |         |        |
    |   1 |  29 | 0xFFFFF80465C28658 | nt!KiIsrThunk+0xe8                                     |         |        |
    |   1 |  30 | 0xFFFFF80465C28660 | nt!KiIsrThunk+0xf0                                     |         |        |
    |   1 |  31 | 0xFFFFF80465C2A590 | nt!KiApcInterrupt                                      |         |        |
    |   1 |  32 | 0xFFFFF80465C2C380 | nt!KiSwInterrupt                                       |         |        |
    |   1 |  33 | 0xFFFFF80465C28678 | nt!KiIsrThunk+0x108                                    |         |        |
    |   1 |  34 | 0xFFFFF80465C28680 | nt!KiIsrThunk+0x110                                    |         |        |
    |   1 |  35 | 0xFFFFF80465C28688 | nt!KiIsrThunk+0x118                                    |         |        |
    |   1 |  36 | 0xFFFFF80465C28690 | nt!KiIsrThunk+0x120                                    |         |        |
    |   1 |  37 | 0xFFFFF80465C28698 | nt!KiIsrThunk+0x128                                    |         |        |
    |   1 |  38 | 0xFFFFF80465C286A0 | nt!KiIsrThunk+0x130                                    |         |        |
    |   1 |  39 | 0xFFFFF80465C286A8 | nt!KiIsrThunk+0x138                                    |         |        |
    |   1 |  40 | 0xFFFFF80465C286B0 | nt!KiIsrThunk+0x140                                    |         |        |
    |   1 |  41 | 0xFFFFF80465C36AC0 | nt!KiRaiseSecurityCheckFailure                         |         |        |
    |   1 |  42 | 0xFFFFF80465C286C0 | nt!KiIsrThunk+0x150                                    |         |        |
    |   1 |  43 | 0xFFFFF80465C286C8 | nt!KiIsrThunk+0x158                                    |         |        |
    |   1 |  44 | 0xFFFFF80465C36E00 | nt!KiRaiseAssertion                                    |         |        |
    |   1 |  45 | 0xFFFFF80465C37140 | nt!KiDebugServiceTrap                                  |         |        |
    |   1 |  46 | 0xFFFFF80465C286E0 | nt!KiIsrThunk+0x170                                    |         |        |
    |   1 |  47 | 0xFFFFF80465C2C9B0 | nt!KiDpcInterrupt                                      |         |        |
    |   1 |  48 | 0xFFFFF80465C2AB90 | nt!KiHvInterrupt                                       |         |        |
    |   1 |  49 | 0xFFFFF80465C2AEB0 | nt!KiVmbusInterrupt0                                   |         |        |
    |   1 |  50 | 0xFFFFF80465C2B1D0 | nt!KiVmbusInterrupt1                                   |         |        |
    |   1 |  51 | 0xFFFFF80465C2B4F0 | nt!KiVmbusInterrupt2                                   |         |        |
    |   1 |  52 | 0xFFFFF80465C2B810 | nt!KiVmbusInterrupt3                                   |         |        |
    |   1 |  53 | 0xFFFFF80465D2A670 | nt!HalpInterruptCmciService                            |         |        |
    |   1 |  54 | 0xFFFFF80465D2A670 | nt!HalpInterruptCmciService                            |         |        |
    |   1 |  55 | 0xFFFFF80465C28728 | nt!KiIsrThunk+0x1b8                                    |         |        |
    |   1 |  56 | 0xFFFFF80465C28730 | nt!KiIsrThunk+0x1c0                                    |         |        |
    |   1 |  57 | 0xFFFFF80465C28738 | nt!KiIsrThunk+0x1c8                                    |         |        |
    |   1 |  58 | 0xFFFFF80465C28740 | nt!KiIsrThunk+0x1d0                                    |         |        |
    |   1 |  59 | 0xFFFFF80465C28748 | nt!KiIsrThunk+0x1d8                                    |         |        |
    |   1 |  60 | 0xFFFFF80465C28750 | nt!KiIsrThunk+0x1e0                                    |         |        |
    |   1 |  61 | 0xFFFFF80465C28758 | nt!KiIsrThunk+0x1e8                                    |         |        |
    |   1 |  62 | 0xFFFFF80465C28760 | nt!KiIsrThunk+0x1f0                                    |         |        |
    |   1 |  63 | 0xFFFFF80465C28768 | nt!KiIsrThunk+0x1f8                                    |         |        |
    |   1 |  64 | 0xFFFFF80465C28770 | nt!KiIsrThunk+0x200                                    |         |        |
    |   1 |  65 | 0xFFFFF80465C28778 | nt!KiIsrThunk+0x208                                    |         |        |
    |   1 |  66 | 0xFFFFF80465C28780 | nt!KiIsrThunk+0x210                                    |         |        |
    |   1 |  67 | 0xFFFFF80465C28788 | nt!KiIsrThunk+0x218                                    |         |        |
    |   1 |  68 | 0xFFFFF80465C28790 | nt!KiIsrThunk+0x220                                    |         |        |
    |   1 |  69 | 0xFFFFF80465C28798 | nt!KiIsrThunk+0x228                                    |         |        |
    |   1 |  70 | 0xFFFFF80465C287A0 | nt!KiIsrThunk+0x230                                    |         |        |
    |   1 |  71 | 0xFFFFF80465C287A8 | nt!KiIsrThunk+0x238                                    |         |        |
    |   1 |  72 | 0xFFFFF80465C287B0 | nt!KiIsrThunk+0x240                                    |         |        |
    |   1 |  73 | 0xFFFFF80465C287B8 | nt!KiIsrThunk+0x248                                    |         |        |
    |   1 |  74 | 0xFFFFF80465C287C0 | nt!KiIsrThunk+0x250                                    |         |        |
    |   1 |  75 | 0xFFFFF80465C287C8 | nt!KiIsrThunk+0x258                                    |         |        |
    |   1 |  76 | 0xFFFFF80465C287D0 | nt!KiIsrThunk+0x260                                    |         |        |
    |   1 |  77 | 0xFFFFF80465C287D8 | nt!KiIsrThunk+0x268                                    |         |        |
    |   1 |  78 | 0xFFFFF80465C287E0 | nt!KiIsrThunk+0x270                                    |         |        |
    |   1 |  79 | 0xFFFFF80465C287E8 | nt!KiIsrThunk+0x278                                    |         |        |
    |   1 |  80 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 |  81 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 |  82 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 |  83 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 |  84 | 0xFFFFF80465C28810 | nt!KiIsrThunk+0x2a0                                    |         |        |
    |   1 |  85 | 0xFFFFF80465C28818 | nt!KiIsrThunk+0x2a8                                    |         |        |
    |   1 |  86 | 0xFFFFF80465C28820 | nt!KiIsrThunk+0x2b0                                    |         |        |
    |   1 |  87 | 0xFFFFF80465C28828 | nt!KiIsrThunk+0x2b8                                    |         |        |
    |   1 |  88 | 0xFFFFF80465C28830 | nt!KiIsrThunk+0x2c0                                    |         |        |
    |   1 |  89 | 0xFFFFF80465C28838 | nt!KiIsrThunk+0x2c8                                    |         |        |
    |   1 |  90 | 0xFFFFF80465C28840 | nt!KiIsrThunk+0x2d0                                    |         |        |
    |   1 |  91 | 0xFFFFF80465C28848 | nt!KiIsrThunk+0x2d8                                    |         |        |
    |   1 |  92 | 0xFFFFF80465C28850 | nt!KiIsrThunk+0x2e0                                    |         |        |
    |   1 |  93 | 0xFFFFF80465C28858 | nt!KiIsrThunk+0x2e8                                    |         |        |
    |   1 |  94 | 0xFFFFF80465C28860 | nt!KiIsrThunk+0x2f0                                    |         |        |
    |   1 |  95 | 0xFFFFF80465C28868 | nt!KiIsrThunk+0x2f8                                    |         |        |
    |   1 |  96 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 |  97 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 |  98 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 |  99 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 100 | 0xFFFFF80465C28890 | nt!KiIsrThunk+0x320                                    |         |        |
    |   1 | 101 | 0xFFFFF80465C28898 | nt!KiIsrThunk+0x328                                    |         |        |
    |   1 | 102 | 0xFFFFF80465C288A0 | nt!KiIsrThunk+0x330                                    |         |        |
    |   1 | 103 | 0xFFFFF80465C288A8 | nt!KiIsrThunk+0x338                                    |         |        |
    |   1 | 104 | 0xFFFFF80465C288B0 | nt!KiIsrThunk+0x340                                    |         |        |
    |   1 | 105 | 0xFFFFF80465C288B8 | nt!KiIsrThunk+0x348                                    |         |        |
    |   1 | 106 | 0xFFFFF80465C288C0 | nt!KiIsrThunk+0x350                                    |         |        |
    |   1 | 107 | 0xFFFFF80465C288C8 | nt!KiIsrThunk+0x358                                    |         |        |
    |   1 | 108 | 0xFFFFF80465C288D0 | nt!KiIsrThunk+0x360                                    |         |        |
    |   1 | 109 | 0xFFFFF80465C288D8 | nt!KiIsrThunk+0x368                                    |         |        |
    |   1 | 110 | 0xFFFFF80465C288E0 | nt!KiIsrThunk+0x370                                    |         |        |
    |   1 | 111 | 0xFFFFF80465C288E8 | nt!KiIsrThunk+0x378                                    |         |        |
    |   1 | 112 | 0xFFFFF806263744B0 | i8042prt!I8042MouseInterruptService                    |         |        |
    |   1 | 113 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 114 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 115 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 116 | 0xFFFFF80465C28910 | nt!KiIsrThunk+0x3a0                                    |         |        |
    |   1 | 117 | 0xFFFFF80465C28918 | nt!KiIsrThunk+0x3a8                                    |         |        |
    |   1 | 118 | 0xFFFFF80465C28920 | nt!KiIsrThunk+0x3b0                                    |         |        |
    |   1 | 119 | 0xFFFFF80465C28928 | nt!KiIsrThunk+0x3b8                                    |         |        |
    |   1 | 120 | 0xFFFFF80465C28930 | nt!KiIsrThunk+0x3c0                                    |         |        |
    |   1 | 121 | 0xFFFFF80465C28938 | nt!KiIsrThunk+0x3c8                                    |         |        |
    |   1 | 122 | 0xFFFFF80465C28940 | nt!KiIsrThunk+0x3d0                                    |         |        |
    |   1 | 123 | 0xFFFFF80465C28948 | nt!KiIsrThunk+0x3d8                                    |         |        |
    |   1 | 124 | 0xFFFFF80465C28950 | nt!KiIsrThunk+0x3e0                                    |         |        |
    |   1 | 125 | 0xFFFFF80465C28958 | nt!KiIsrThunk+0x3e8                                    |         |        |
    |   1 | 126 | 0xFFFFF80465C28960 | nt!KiIsrThunk+0x3f0                                    |         |        |
    |   1 | 127 | 0xFFFFF80465C28968 | nt!KiIsrThunk+0x3f8                                    |         |        |
    |   1 | 128 | 0xFFFFF80626371660 | i8042prt!I8042KeyboardInterruptService                 |         |        |
    |   1 | 129 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 130 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 131 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 132 | 0xFFFFF80465C28990 | nt!KiIsrThunk+0x420                                    |         |        |
    |   1 | 133 | 0xFFFFF80465C28998 | nt!KiIsrThunk+0x428                                    |         |        |
    |   1 | 134 | 0xFFFFF80465C289A0 | nt!KiIsrThunk+0x430                                    |         |        |
    |   1 | 135 | 0xFFFFF80465C289A8 | nt!KiIsrThunk+0x438                                    |         |        |
    |   1 | 136 | 0xFFFFF80465C289B0 | nt!KiIsrThunk+0x440                                    |         |        |
    |   1 | 137 | 0xFFFFF80465C289B8 | nt!KiIsrThunk+0x448                                    |         |        |
    |   1 | 138 | 0xFFFFF80465C289C0 | nt!KiIsrThunk+0x450                                    |         |        |
    |   1 | 139 | 0xFFFFF80465C289C8 | nt!KiIsrThunk+0x458                                    |         |        |
    |   1 | 140 | 0xFFFFF80465C289D0 | nt!KiIsrThunk+0x460                                    |         |        |
    |   1 | 141 | 0xFFFFF80465C289D8 | nt!KiIsrThunk+0x468                                    |         |        |
    |   1 | 142 | 0xFFFFF80465C289E0 | nt!KiIsrThunk+0x470                                    |         |        |
    |   1 | 143 | 0xFFFFF80465C289E8 | nt!KiIsrThunk+0x478                                    |         |        |
    |   1 | 144 | 0xFFFFF80465C289F0 | nt!KiIsrThunk+0x480                                    |         |        |
    |   1 | 145 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 146 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 147 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 148 | 0xFFFFF80465C28A10 | nt!KiIsrThunk+0x4a0                                    |         |        |
    |   1 | 149 | 0xFFFFF80465C28A18 | nt!KiIsrThunk+0x4a8                                    |         |        |
    |   1 | 150 | 0xFFFFF80465C28A20 | nt!KiIsrThunk+0x4b0                                    |         |        |
    |   1 | 151 | 0xFFFFF80465C28A28 | nt!KiIsrThunk+0x4b8                                    |         |        |
    |   1 | 152 | 0xFFFFF80465C28A30 | nt!KiIsrThunk+0x4c0                                    |         |        |
    |   1 | 153 | 0xFFFFF80465C28A38 | nt!KiIsrThunk+0x4c8                                    |         |        |
    |   1 | 154 | 0xFFFFF80465C28A40 | nt!KiIsrThunk+0x4d0                                    |         |        |
    |   1 | 155 | 0xFFFFF80465C28A48 | nt!KiIsrThunk+0x4d8                                    |         |        |
    |   1 | 156 | 0xFFFFF80465C28A50 | nt!KiIsrThunk+0x4e0                                    |         |        |
    |   1 | 157 | 0xFFFFF80465C28A58 | nt!KiIsrThunk+0x4e8                                    |         |        |
    |   1 | 158 | 0xFFFFF80465C28A60 | nt!KiIsrThunk+0x4f0                                    |         |        |
    |   1 | 159 | 0xFFFFF80465C28A68 | nt!KiIsrThunk+0x4f8                                    |         |        |
    |   1 | 160 | 0xFFFFF80465C28A70 | nt!KiIsrThunk+0x500                                    |         |        |
    |   1 | 161 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 162 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 163 | 0xFFFFF804674854D0 | ataport!IdePortInterrupt                               |         |        |
    |   1 | 164 | 0xFFFFF80465C28A90 | nt!KiIsrThunk+0x520                                    |         |        |
    |   1 | 165 | 0xFFFFF80465C28A98 | nt!KiIsrThunk+0x528                                    |         |        |
    |   1 | 166 | 0xFFFFF80465C28AA0 | nt!KiIsrThunk+0x530                                    |         |        |
    |   1 | 167 | 0xFFFFF80465C28AA8 | nt!KiIsrThunk+0x538                                    |         |        |
    |   1 | 168 | 0xFFFFF80465C28AB0 | nt!KiIsrThunk+0x540                                    |         |        |
    |   1 | 169 | 0xFFFFF80465C28AB8 | nt!KiIsrThunk+0x548                                    |         |        |
    |   1 | 170 | 0xFFFFF80465C28AC0 | nt!KiIsrThunk+0x550                                    |         |        |
    |   1 | 171 | 0xFFFFF80465C28AC8 | nt!KiIsrThunk+0x558                                    |         |        |
    |   1 | 172 | 0xFFFFF80465C28AD0 | nt!KiIsrThunk+0x560                                    |         |        |
    |   1 | 173 | 0xFFFFF80465C28AD8 | nt!KiIsrThunk+0x568                                    |         |        |
    |   1 | 174 | 0xFFFFF80465C28AE0 | nt!KiIsrThunk+0x570                                    |         |        |
    |   1 | 175 | 0xFFFFF80465C28AE8 | nt!KiIsrThunk+0x578                                    |         |        |
    |   1 | 176 | 0xFFFFF80466F97F40 | ACPI!ACPIInterruptServiceRoutine                       |         |        |
    |   1 | 177 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 178 | 0xFFFFF80465A4A720 | nt!KiInterruptMessageDispatch                          |         |        |
    |   1 | 179 | 0xFFFFF804674854D0 | ataport!IdePortInterrupt                               |         |        |
    |   1 | 180 | 0xFFFFF80626C30FE0 | dxgkrnl!DpiFdoLineInterruptRoutine                     |         |        |
    |   1 | 181 | 0xFFFFF80465C28B18 | nt!KiIsrThunk+0x5a8                                    |         |        |
    |   1 | 182 | 0xFFFFF80465C28B20 | nt!KiIsrThunk+0x5b0                                    |         |        |
    |   1 | 183 | 0xFFFFF80465C28B28 | nt!KiIsrThunk+0x5b8                                    |         |        |
    |   1 | 184 | 0xFFFFF80465C28B30 | nt!KiIsrThunk+0x5c0                                    |         |        |
    |   1 | 185 | 0xFFFFF80465C28B38 | nt!KiIsrThunk+0x5c8                                    |         |        |
    |   1 | 186 | 0xFFFFF80465C28B40 | nt!KiIsrThunk+0x5d0                                    |         |        |
    |   1 | 187 | 0xFFFFF80465C28B48 | nt!KiIsrThunk+0x5d8                                    |         |        |
    |   1 | 188 | 0xFFFFF80465C28B50 | nt!KiIsrThunk+0x5e0                                    |         |        |
    |   1 | 189 | 0xFFFFF80465C28B58 | nt!KiIsrThunk+0x5e8                                    |         |        |
    |   1 | 190 | 0xFFFFF80465C28B60 | nt!KiIsrThunk+0x5f0                                    |         |        |
    |   1 | 191 | 0xFFFFF80465C28B68 | nt!KiIsrThunk+0x5f8                                    |         |        |
    |   1 | 192 | 0xFFFFF80465C28B70 | nt!KiIsrThunk+0x600                                    |         |        |
    |   1 | 193 | 0xFFFFF80465C28B78 | nt!KiIsrThunk+0x608                                    |         |        |
    |   1 | 194 | 0xFFFFF80465C28B80 | nt!KiIsrThunk+0x610                                    |         |        |
    |   1 | 195 | 0xFFFFF80465C28B88 | nt!KiIsrThunk+0x618                                    |         |        |
    |   1 | 196 | 0xFFFFF80465C28B90 | nt!KiIsrThunk+0x620                                    |         |        |
    |   1 | 197 | 0xFFFFF80465C28B98 | nt!KiIsrThunk+0x628                                    |         |        |
    |   1 | 198 | 0xFFFFF80465C28BA0 | nt!KiIsrThunk+0x630                                    |         |        |
    |   1 | 199 | 0xFFFFF80465C28BA8 | nt!KiIsrThunk+0x638                                    |         |        |
    |   1 | 200 | 0xFFFFF80465C28BB0 | nt!KiIsrThunk+0x640                                    |         |        |
    |   1 | 201 | 0xFFFFF80465C28BB8 | nt!KiIsrThunk+0x648                                    |         |        |
    |   1 | 202 | 0xFFFFF80465C28BC0 | nt!KiIsrThunk+0x650                                    |         |        |
    |   1 | 203 | 0xFFFFF80465C28BC8 | nt!KiIsrThunk+0x658                                    |         |        |
    |   1 | 204 | 0xFFFFF80465C28BD0 | nt!KiIsrThunk+0x660                                    |         |        |
    |   1 | 205 | 0xFFFFF80465C28BD8 | nt!KiIsrThunk+0x668                                    |         |        |
    |   1 | 206 | 0xFFFFF80465D22C60 | nt!HalpIommuInterruptRoutine                           |         |        |
    |   1 | 207 | 0xFFFFF80465C28BE8 | nt!KiIsrThunk+0x678                                    |         |        |
    |   1 | 208 | 0xFFFFF80465C28BF0 | nt!KiIsrThunk+0x680                                    |         |        |
    |   1 | 209 | 0xFFFFF80465A94C10 | nt!HalpTimerClockInterrupt                             |         |        |
    |   1 | 210 | 0xFFFFF80465A96F70 | nt!HalpTimerClockIpiRoutine                            |         |        |
    |   1 | 211 | 0xFFFFF80465C28C08 | nt!KiIsrThunk+0x698                                    |         |        |
    |   1 | 212 | 0xFFFFF80465C28C10 | nt!KiIsrThunk+0x6a0                                    |         |        |
    |   1 | 213 | 0xFFFFF80465C28C18 | nt!KiIsrThunk+0x6a8                                    |         |        |
    |   1 | 214 | 0xFFFFF80465C28C20 | nt!KiIsrThunk+0x6b0                                    |         |        |
    |   1 | 215 | 0xFFFFF80465D2A6B0 | nt!HalpInterruptRebootService                          |         |        |
    |   1 | 216 | 0xFFFFF80465D2A730 | nt!HalpInterruptStubService                            |         |        |
    |   1 | 217 | 0xFFFFF80465C28C38 | nt!KiIsrThunk+0x6c8                                    |         |        |
    |   1 | 218 | 0xFFFFF80465C28C40 | nt!KiIsrThunk+0x6d0                                    |         |        |
    |   1 | 219 | 0xFFFFF80465C28C48 | nt!KiIsrThunk+0x6d8                                    |         |        |
    |   1 | 220 | 0xFFFFF80465C28C50 | nt!KiIsrThunk+0x6e0                                    |         |        |
    |   1 | 221 | 0xFFFFF80465C28C58 | nt!KiIsrThunk+0x6e8                                    |         |        |
    |   1 | 222 | 0xFFFFF80465C28C60 | nt!KiIsrThunk+0x6f0                                    |         |        |
    |   1 | 223 | 0xFFFFF80465D2A700 | nt!HalpInterruptSpuriousService                        |         |        |
    |   1 | 224 | 0xFFFFF80465C28C70 | nt!KiIsrThunk+0x700                                    |         |        |
    |   1 | 225 | 0xFFFFF80465C2CF10 | nt!KiIpiInterrupt                                      |         |        |
    |   1 | 226 | 0xFFFFF80465BBFC10 | nt!HalpInterruptLocalErrorService                      |         |        |
    |   1 | 227 | 0xFFFFF80465D2A690 | nt!HalpInterruptDeferredRecoveryService                |         |        |
    |   1 | 228 | 0xFFFFF80465C28C90 | nt!KiIsrThunk+0x720                                    |         |        |
    |   1 | 229 | 0xFFFFF80465C28C98 | nt!KiIsrThunk+0x728                                    |         |        |
    |   1 | 230 | 0xFFFFF80465C28CA0 | nt!KiIsrThunk+0x730                                    |         |        |
    |   1 | 231 | 0xFFFFF80465C28CA8 | nt!KiIsrThunk+0x738                                    |         |        |
    |   1 | 232 | 0xFFFFF80465C28CB0 | nt!KiIsrThunk+0x740                                    |         |        |
    |   1 | 233 | 0xFFFFF80465C28CB8 | nt!KiIsrThunk+0x748                                    |         |        |
    |   1 | 234 | 0xFFFFF80465C28CC0 | nt!KiIsrThunk+0x750                                    |         |        |
    |   1 | 235 | 0xFFFFF80465C28CC8 | nt!KiIsrThunk+0x758                                    |         |        |
    |   1 | 236 | 0xFFFFF80465C28CD0 | nt!KiIsrThunk+0x760                                    |         |        |
    |   1 | 237 | 0xFFFFF80465C28CD8 | nt!KiIsrThunk+0x768                                    |         |        |
    |   1 | 238 | 0xFFFFF80465C28CE0 | nt!KiIsrThunk+0x770                                    |         |        |
    |   1 | 239 | 0xFFFFF80465C28CE8 | nt!KiIsrThunk+0x778                                    |         |        |
    |   1 | 240 | 0xFFFFF80465C28CF0 | nt!KiIsrThunk+0x780                                    |         |        |
    |   1 | 241 | 0xFFFFF80465C28CF8 | nt!KiIsrThunk+0x788                                    |         |        |
    |   1 | 242 | 0xFFFFF80465C28D00 | nt!KiIsrThunk+0x790                                    |         |        |
    |   1 | 243 | 0xFFFFF80465C28D08 | nt!KiIsrThunk+0x798                                    |         |        |
    |   1 | 244 | 0xFFFFF80465C28D10 | nt!KiIsrThunk+0x7a0                                    |         |        |
    |   1 | 245 | 0xFFFFF80465C28D18 | nt!KiIsrThunk+0x7a8                                    |         |        |
    |   1 | 246 | 0xFFFFF80465C28D20 | nt!KiIsrThunk+0x7b0                                    |         |        |
    |   1 | 247 | 0xFFFFF80465C28D28 | nt!KiIsrThunk+0x7b8                                    |         |        |
    |   1 | 248 | 0xFFFFF80465C28D30 | nt!KiIsrThunk+0x7c0                                    |         |        |
    |   1 | 249 | 0xFFFFF80465C28D38 | nt!KiIsrThunk+0x7c8                                    |         |        |
    |   1 | 250 | 0xFFFFF80465C28D40 | nt!KiIsrThunk+0x7d0                                    |         |        |
    |   1 | 251 | 0xFFFFF80465C28D48 | nt!KiIsrThunk+0x7d8                                    |         |        |
    |   1 | 252 | 0xFFFFF80465C28D50 | nt!KiIsrThunk+0x7e0                                    |         |        |
    |   1 | 253 | 0xFFFFF80465D2CDB0 | nt!HalpTimerProfileInterrupt                           |         |        |
    |   1 | 254 | 0xFFFFF80465C5A9C0 | nt!HalpPerfInterrupt                                   |         |        |
    |   1 | 255 | 0xFFFFF80465C28D68 | nt!KiIsrThunk+0x7f8                                    |         |        |

0: kd> !idt -a

Dumping IDT: fffff80465083000

00: fffff80465c30e00 nt!KiDivideErrorFault
01: fffff80465c31100 nt!KiDebugTrapOrFault  Stack = 0xFFFFF804650C3000
02: fffff80465c316c0 nt!KiNmiInterrupt  Stack = 0xFFFFF804650B5000
03: fffff80465c31c00 nt!KiBreakpointTrap
04: fffff80465c31f40 nt!KiOverflowTrap
05: fffff80465c32240 nt!KiBoundFault
06: fffff80465c32780 nt!KiInvalidOpcodeFault
07: fffff80465c32c80 nt!KiNpxNotAvailableFault
08: fffff80465c33000 nt!KiDoubleFaultAbort  Stack = 0xFFFFF804650AE000
09: fffff80465c33300 nt!KiNpxSegmentOverrunAbort
0a: fffff80465c33640 nt!KiInvalidTssFault
0b: fffff80465c33980 nt!KiSegmentNotPresentFault
0c: fffff80465c33d40 nt!KiStackFault
0d: fffff80465c34080 nt!KiGeneralProtectionFault
0e: fffff80465c343c0 nt!KiPageFault
0f: fffff80465c285e8 nt!KiIsrThunk+0x78
10: fffff80465c34a00 nt!KiFloatingErrorFault
11: fffff80465c34d80 nt!KiAlignmentFault
12: fffff80465c35080 nt!KiMcheckAbort   Stack = 0xFFFFF804650BC000
13: fffff80465c35c40 nt!KiXmmException
14: fffff80465c36000 nt!KiVirtualizationException
15: fffff80465c36540 nt!KiControlProtectionFault
16: fffff80465c28620 nt!KiIsrThunk+0xB0
17: fffff80465c28628 nt!KiIsrThunk+0xB8
18: fffff80465c28630 nt!KiIsrThunk+0xC0
19: fffff80465c28638 nt!KiIsrThunk+0xC8
1a: fffff80465c28640 nt!KiIsrThunk+0xD0
1b: fffff80465c28648 nt!KiIsrThunk+0xD8
1c: fffff80465c28650 nt!KiIsrThunk+0xE0
1d: fffff80465c28658 nt!KiIsrThunk+0xE8
1e: fffff80465c28660 nt!KiIsrThunk+0xF0
1f: fffff80465c2a590 nt!KiApcInterrupt
20: fffff80465c2c380 nt!KiSwInterrupt
21: fffff80465c28678 nt!KiIsrThunk+0x108
22: fffff80465c28680 nt!KiIsrThunk+0x110
23: fffff80465c28688 nt!KiIsrThunk+0x118
24: fffff80465c28690 nt!KiIsrThunk+0x120
25: fffff80465c28698 nt!KiIsrThunk+0x128
26: fffff80465c286a0 nt!KiIsrThunk+0x130
27: fffff80465c286a8 nt!KiIsrThunk+0x138
28: fffff80465c286b0 nt!KiIsrThunk+0x140
29: fffff80465c36ac0 nt!KiRaiseSecurityCheckFailure
2a: fffff80465c286c0 nt!KiIsrThunk+0x150
2b: fffff80465c286c8 nt!KiIsrThunk+0x158
2c: fffff80465c36e00 nt!KiRaiseAssertion
2d: fffff80465c37140 nt!KiDebugServiceTrap
2e: fffff80465c286e0 nt!KiIsrThunk+0x170
2f: fffff80465c2c9b0 nt!KiDpcInterrupt
30: fffff80465c2ab90 nt!KiHvInterrupt
31: fffff80465c2aeb0 nt!KiVmbusInterrupt0
32: fffff80465c2b1d0 nt!KiVmbusInterrupt1
33: fffff80465c2b4f0 nt!KiVmbusInterrupt2
34: fffff80465c2b810 nt!KiVmbusInterrupt3
35: fffff80465c28718 nt!HalpInterruptCmciService (KINTERRUPT fffff80466506490)
36: fffff80465c28720 nt!HalpInterruptCmciService (KINTERRUPT fffff804665066d0)
37: fffff80465c28728 nt!KiIsrThunk+0x1B8
38: fffff80465c28730 nt!KiIsrThunk+0x1C0
39: fffff80465c28738 nt!KiIsrThunk+0x1C8
3a: fffff80465c28740 nt!KiIsrThunk+0x1D0
3b: fffff80465c28748 nt!KiIsrThunk+0x1D8
3c: fffff80465c28750 nt!KiIsrThunk+0x1E0
3d: fffff80465c28758 nt!KiIsrThunk+0x1E8
3e: fffff80465c28760 nt!KiIsrThunk+0x1F0
3f: fffff80465c28768 nt!KiIsrThunk+0x1F8
40: fffff80465c28770 nt!KiIsrThunk+0x200
41: fffff80465c28778 nt!KiIsrThunk+0x208
42: fffff80465c28780 nt!KiIsrThunk+0x210
43: fffff80465c28788 nt!KiIsrThunk+0x218
44: fffff80465c28790 nt!KiIsrThunk+0x220
45: fffff80465c28798 nt!KiIsrThunk+0x228
46: fffff80465c287a0 nt!KiIsrThunk+0x230
47: fffff80465c287a8 nt!KiIsrThunk+0x238
48: fffff80465c287b0 nt!KiIsrThunk+0x240
49: fffff80465c287b8 nt!KiIsrThunk+0x248
4a: fffff80465c287c0 nt!KiIsrThunk+0x250
4b: fffff80465c287c8 nt!KiIsrThunk+0x258
4c: fffff80465c287d0 nt!KiIsrThunk+0x260
4d: fffff80465c287d8 nt!KiIsrThunk+0x268
4e: fffff80465c287e0 nt!KiIsrThunk+0x270
4f: fffff80465c287e8 nt!KiIsrThunk+0x278
50: fffff80465c287f0 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfac80)
51: fffff80465c287f8 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfa3c0)
52: fffff80465c28800 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa00120305a00)
53: fffff80465c28808 stornvme!NVMeHwMSIInterrupt (STORPORT) (KINTERRUPT ffffa00120305000)
54: fffff80465c28810 nt!KiIsrThunk+0x2A0
55: fffff80465c28818 nt!KiIsrThunk+0x2A8
56: fffff80465c28820 nt!KiIsrThunk+0x2B0
57: fffff80465c28828 nt!KiIsrThunk+0x2B8
58: fffff80465c28830 nt!KiIsrThunk+0x2C0
59: fffff80465c28838 nt!KiIsrThunk+0x2C8
5a: fffff80465c28840 nt!KiIsrThunk+0x2D0
5b: fffff80465c28848 nt!KiIsrThunk+0x2D8
5c: fffff80465c28850 nt!KiIsrThunk+0x2E0
5d: fffff80465c28858 nt!KiIsrThunk+0x2E8
5e: fffff80465c28860 nt!KiIsrThunk+0x2F0
5f: fffff80465c28868 nt!KiIsrThunk+0x2F8
60: fffff80465c28870 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa001203058c0)
61: fffff80465c28878 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfa500)
62: fffff80465c28880 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa00120305b40)
63: fffff80465c28888 stornvme!NVMeHwMSIInterrupt (STORPORT) (KINTERRUPT ffffa00120305140)
64: fffff80465c28890 nt!KiIsrThunk+0x320
65: fffff80465c28898 nt!KiIsrThunk+0x328
66: fffff80465c288a0 nt!KiIsrThunk+0x330
67: fffff80465c288a8 nt!KiIsrThunk+0x338
68: fffff80465c288b0 nt!KiIsrThunk+0x340
69: fffff80465c288b8 nt!KiIsrThunk+0x348
6a: fffff80465c288c0 nt!KiIsrThunk+0x350
6b: fffff80465c288c8 nt!KiIsrThunk+0x358
6c: fffff80465c288d0 nt!KiIsrThunk+0x360
6d: fffff80465c288d8 nt!KiIsrThunk+0x368
6e: fffff80465c288e0 nt!KiIsrThunk+0x370
6f: fffff80465c288e8 nt!KiIsrThunk+0x378
70: fffff80465c288f0 i8042prt!I8042MouseInterruptService (KINTERRUPT ffffa00123903c80)
71: fffff80465c288f8 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfa640)
72: fffff80465c28900 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa00120305c80)
73: fffff80465c28908 storahci!AhciHwMSIInterrupt (STORPORT) (KINTERRUPT ffffa00120305280)
74: fffff80465c28910 nt!KiIsrThunk+0x3A0
75: fffff80465c28918 nt!KiIsrThunk+0x3A8
76: fffff80465c28920 nt!KiIsrThunk+0x3B0
77: fffff80465c28928 nt!KiIsrThunk+0x3B8
78: fffff80465c28930 nt!KiIsrThunk+0x3C0
79: fffff80465c28938 nt!KiIsrThunk+0x3C8
7a: fffff80465c28940 nt!KiIsrThunk+0x3D0
7b: fffff80465c28948 nt!KiIsrThunk+0x3D8
7c: fffff80465c28950 nt!KiIsrThunk+0x3E0
7d: fffff80465c28958 nt!KiIsrThunk+0x3E8
7e: fffff80465c28960 nt!KiIsrThunk+0x3F0
7f: fffff80465c28968 nt!KiIsrThunk+0x3F8
80: fffff80465c28970 i8042prt!I8042KeyboardInterruptService (KINTERRUPT ffffa00123903dc0)
81: fffff80465c28978 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfa780)
82: fffff80465c28980 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa00120305dc0)
83: fffff80465c28988 vmci+0x31c0 (KINTERRUPT ffffa00120305640)
84: fffff80465c28990 ndis!ndisMiniportMessageIsr (KINTERRUPT ffffa001239038c0)
85: fffff80465c28998 nt!KiIsrThunk+0x428
86: fffff80465c289a0 nt!KiIsrThunk+0x430
87: fffff80465c289a8 nt!KiIsrThunk+0x438
88: fffff80465c289b0 nt!KiIsrThunk+0x440
89: fffff80465c289b8 nt!KiIsrThunk+0x448
8a: fffff80465c289c0 nt!KiIsrThunk+0x450
8b: fffff80465c289c8 nt!KiIsrThunk+0x458
8c: fffff80465c289d0 nt!KiIsrThunk+0x460
8d: fffff80465c289d8 nt!KiIsrThunk+0x468
8e: fffff80465c289e0 nt!KiIsrThunk+0x470
8f: fffff80465c289e8 nt!KiIsrThunk+0x478
90: fffff80465c289f0 nt!KiIsrThunk+0x480
91: fffff80465c289f8 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfa8c0)
92: fffff80465c28a00 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfa000)
93: fffff80465c28a08 vmci+0x31c0 (KINTERRUPT ffffa00120305780)
94: fffff80465c28a10 ndis!ndisMiniportMessageIsr (KINTERRUPT ffffa00123903a00)
95: fffff80465c28a18 nt!KiIsrThunk+0x4A8
96: fffff80465c28a20 nt!KiIsrThunk+0x4B0
97: fffff80465c28a28 nt!KiIsrThunk+0x4B8
98: fffff80465c28a30 nt!KiIsrThunk+0x4C0
99: fffff80465c28a38 nt!KiIsrThunk+0x4C8
9a: fffff80465c28a40 nt!KiIsrThunk+0x4D0
9b: fffff80465c28a48 nt!KiIsrThunk+0x4D8
9c: fffff80465c28a50 nt!KiIsrThunk+0x4E0
9d: fffff80465c28a58 nt!KiIsrThunk+0x4E8
9e: fffff80465c28a60 nt!KiIsrThunk+0x4F0
9f: fffff80465c28a68 nt!KiIsrThunk+0x4F8
a0: fffff80465c28a70 nt!KiIsrThunk+0x500
a1: fffff80465c28a78 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfaa00)
a2: fffff80465c28a80 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfa140)
a3: fffff80465c28a88 ataport!IdePortInterrupt (KINTERRUPT ffffa001203053c0)
a4: fffff80465c28a90 ndis!ndisMiniportMessageIsr (KINTERRUPT ffffa00123903b40)
a5: fffff80465c28a98 nt!KiIsrThunk+0x528
a6: fffff80465c28aa0 nt!KiIsrThunk+0x530
a7: fffff80465c28aa8 nt!KiIsrThunk+0x538
a8: fffff80465c28ab0 nt!KiIsrThunk+0x540
a9: fffff80465c28ab8 nt!KiIsrThunk+0x548
aa: fffff80465c28ac0 nt!KiIsrThunk+0x550
ab: fffff80465c28ac8 nt!KiIsrThunk+0x558
ac: fffff80465c28ad0 nt!KiIsrThunk+0x560
ad: fffff80465c28ad8 nt!KiIsrThunk+0x568
ae: fffff80465c28ae0 nt!KiIsrThunk+0x570
af: fffff80465c28ae8 nt!KiIsrThunk+0x578
b0: fffff80465c28af0 ACPI!ACPIInterruptServiceRoutine (KINTERRUPT ffffa0011fbfadc0)
b1: fffff80465c28af8 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfab40)
b2: fffff80465c28b00 pci!ExpressRootPortMessageRoutine (KINTERRUPT ffffa0011fbfa280)
b3: fffff80465c28b08 ataport!IdePortInterrupt (KINTERRUPT ffffa00120305500)
b4: fffff80465c28b10 dxgkrnl!DpiFdoLineInterruptRoutine (KINTERRUPT ffffa00123903780)
b5: fffff80465c28b18 nt!KiIsrThunk+0x5A8
b6: fffff80465c28b20 nt!KiIsrThunk+0x5B0
b7: fffff80465c28b28 nt!KiIsrThunk+0x5B8
b8: fffff80465c28b30 nt!KiIsrThunk+0x5C0
b9: fffff80465c28b38 nt!KiIsrThunk+0x5C8
ba: fffff80465c28b40 nt!KiIsrThunk+0x5D0
bb: fffff80465c28b48 nt!KiIsrThunk+0x5D8
bc: fffff80465c28b50 nt!KiIsrThunk+0x5E0
bd: fffff80465c28b58 nt!KiIsrThunk+0x5E8
be: fffff80465c28b60 nt!KiIsrThunk+0x5F0
bf: fffff80465c28b68 nt!KiIsrThunk+0x5F8
c0: fffff80465c28b70 nt!KiIsrThunk+0x600
c1: fffff80465c28b78 nt!KiIsrThunk+0x608
c2: fffff80465c28b80 nt!KiIsrThunk+0x610
c3: fffff80465c28b88 nt!KiIsrThunk+0x618
c4: fffff80465c28b90 nt!KiIsrThunk+0x620
c5: fffff80465c28b98 nt!KiIsrThunk+0x628
c6: fffff80465c28ba0 nt!KiIsrThunk+0x630
c7: fffff80465c28ba8 nt!KiIsrThunk+0x638
c8: fffff80465c28bb0 nt!KiIsrThunk+0x640
c9: fffff80465c28bb8 nt!KiIsrThunk+0x648
ca: fffff80465c28bc0 nt!KiIsrThunk+0x650
cb: fffff80465c28bc8 nt!KiIsrThunk+0x658
cc: fffff80465c28bd0 nt!KiIsrThunk+0x660
cd: fffff80465c28bd8 nt!KiIsrThunk+0x668
ce: fffff80465c28be0 nt!HalpIommuInterruptRoutine (KINTERRUPT fffff804665070f0)
cf: fffff80465c28be8 nt!KiIsrThunk+0x678
d0: fffff80465c28bf0 nt!KiIsrThunk+0x680
d1: fffff80465c28bf8 nt!HalpTimerClockInterrupt (KINTERRUPT fffff80466506eb0)
d2: fffff80465c28c00 nt!HalpTimerClockIpiRoutine (KINTERRUPT fffff80466506d90)
d3: fffff80465c28c08 nt!KiIsrThunk+0x698
d4: fffff80465c28c10 nt!KiIsrThunk+0x6A0
d5: fffff80465c28c18 nt!KiIsrThunk+0x6A8
d6: fffff80465c28c20 nt!KiIsrThunk+0x6B0
d7: fffff80465c28c28 nt!HalpInterruptRebootService (KINTERRUPT fffff80466506b50)
d8: fffff80465c28c30 nt!HalpInterruptStubService (KINTERRUPT fffff80466506910)
d9: fffff80465c28c38 nt!KiIsrThunk+0x6C8
da: fffff80465c28c40 nt!KiIsrThunk+0x6D0
db: fffff80465c28c48 nt!KiIsrThunk+0x6D8
dc: fffff80465c28c50 nt!KiIsrThunk+0x6E0
dd: fffff80465c28c58 nt!KiIsrThunk+0x6E8
de: fffff80465c28c60 nt!KiIsrThunk+0x6F0
df: fffff80465c28c68 nt!HalpInterruptSpuriousService (KINTERRUPT fffff804665067f0)
e0: fffff80465c28c70 nt!KiIsrThunk+0x700
e1: fffff80465c2cf10 nt!KiIpiInterrupt
e2: fffff80465c28c80 nt!HalpInterruptLocalErrorService (KINTERRUPT fffff80466506a30)
e3: fffff80465c28c88 nt!HalpInterruptDeferredRecoveryService (KINTERRUPT fffff804665065b0)
e4: fffff80465c28c90 nt!KiIsrThunk+0x720
e5: fffff80465c28c98 nt!KiIsrThunk+0x728
e6: fffff80465c28ca0 nt!KiIsrThunk+0x730
e7: fffff80465c28ca8 nt!KiIsrThunk+0x738
e8: fffff80465c28cb0 nt!KiIsrThunk+0x740
e9: fffff80465c28cb8 nt!KiIsrThunk+0x748
ea: fffff80465c28cc0 nt!KiIsrThunk+0x750
eb: fffff80465c28cc8 nt!KiIsrThunk+0x758
ec: fffff80465c28cd0 nt!KiIsrThunk+0x760
ed: fffff80465c28cd8 nt!KiIsrThunk+0x768
ee: fffff80465c28ce0 nt!KiIsrThunk+0x770
ef: fffff80465c28ce8 nt!KiIsrThunk+0x778
f0: fffff80465c28cf0 nt!KiIsrThunk+0x780
f1: fffff80465c28cf8 nt!KiIsrThunk+0x788
f2: fffff80465c28d00 nt!KiIsrThunk+0x790
f3: fffff80465c28d08 nt!KiIsrThunk+0x798
f4: fffff80465c28d10 nt!KiIsrThunk+0x7A0
f5: fffff80465c28d18 nt!KiIsrThunk+0x7A8
f6: fffff80465c28d20 nt!KiIsrThunk+0x7B0
f7: fffff80465c28d28 nt!KiIsrThunk+0x7B8
f8: fffff80465c28d30 nt!KiIsrThunk+0x7C0
f9: fffff80465c28d38 nt!KiIsrThunk+0x7C8
fa: fffff80465c28d40 nt!KiIsrThunk+0x7D0
fb: fffff80465c28d48 nt!KiIsrThunk+0x7D8
fc: fffff80465c28d50 nt!KiIsrThunk+0x7E0
fd: fffff80465c28d58 nt!HalpTimerProfileInterrupt (KINTERRUPT fffff80466506fd0)
fe: fffff80465c28d60 nt!HalpPerfInterrupt (KINTERRUPT fffff80466506c70)
ff: fffff80465c28d68 nt!KiIsrThunk+0x7F8

0: kd> .unload ReadIDTDbgExt.dll
Unloading ReadIDTDbgExt extension DLL
```

## Tested OS Versions
- `Windows 11 21H2 Build 22000 Revision 675 64-bit`

## References
1. [Interrupt Dispatching Internals](https://codemachine.com/articles/interrupt_dispatching.html)
2. [Interrupt Descriptor Table](https://wiki.osdev.org/Interrupt_Descriptor_Table)
3. [Interrupt Handling and Stack Switching in x86-64 Architecture](https://theokwebb.github.io/posts/interrupt-handling-and-stack-switching/)
4. [Interrupt Descriptor Table - IDT](https://www.ired.team/miscellaneous-reversing-forensics/windows-kernel-internals/interrupt-descriptor-table-idt)
5. [SwishDbgExt](https://github.com/MagnetForensics/SwishDbgExt)