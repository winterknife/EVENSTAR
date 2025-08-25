# EVENSTAR - DetectProcessorMode

## Version
- `v1.0.0`

## Brief
- `ISA: x86`
- `Mode: Protected, Compatibility, Long`
- `Bitness: 32-bit, 64-bit`
- `CPL: 0, 3`
- `OS: Windows`
- `Language: Python`
- Script that demonstrates the difference in `x86` instruction decoding in `IA-32` and `IA-32e` modes to determine the execution mode of the processor at run-time

## Usage
- To generate 32-bit `x86` `MessageBox` shellcode using the `Metasploit` framework
```bash
msfvenom -a x86 --platform Windows --payload windows/messagebox -f raw -o shellcode_x86.bin
```
- To generate 64-bit `x86` `MessageBox` shellcode using the `Metasploit` framework
```bash
msfvenom -a x64 --platform Windows --payload windows/x64/messagebox -f raw -o shellcode_x64.bin
```
- To create multi-bitness `x86` `MessageBox` shellcode
```cmd
[...]>python.exe merge_shellcode.py
[-] Invalid args.

[+] Usage: python.exe merge_shellcode.py [x86-32 shellcode input filename] [x86-64 shellcode input filename] [multi-bitness x86 shellcode output filename]

    [x86-32 shellcode input filename]             - Path to 32-bit x86 PIC file which is to be combined into a single-shot dual-mode payload
    [x86-64 shellcode input filename]             - Path to 64-bit x86 PIC file which is to be combined into a single-shot dual-mode payload
    [multi-bitness x86 shellcode output filename] - Path to multi-bitness x86 PIC file which will be saved to disk after merging (can be executed in both IA-32 and IA-32e mode)

    Example: python.exe merge_shellcode.py shellcode_x86.bin shellcode_x64.bin shellcode_multi.bin

[...]>python.exe merge_shellcode.py shellcode_x86.bin shellcode_x64.bin shellcode_multi.bin
[+] Merged x86-32 and x86-64 shellcode into multi-bitness x86 shellcode.
```

## Tested OS Versions
- `Windows 11 21H2 Build 22000 Revision 675 64-bit`

## References
1. [Architecture Detection (x86 or x64) Assembly Stub](https://zerosum0x0.blogspot.com/2014/12/detect-x86-or-x64-assembly-stub.html)
2. [DoublePulsar Initial SMB Backdoor Ring 0 Shellcode Analysis](https://zerosum0x0.blogspot.com/2017/04/doublepulsar-initial-smb-backdoor-ring.html)
3. [eternalblue_sc_merge.py](https://github.com/worawit/MS17-010/blob/master/shellcode/eternalblue_sc_merge.py)
4. [Multi-bitness x86 code](https://pagedout.institute/download/PagedOut_001_beta1.pdf)
5. [Full Fat Shellcode](https://winternl.com/full-fat-shellcode/)