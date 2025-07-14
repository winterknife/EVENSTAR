#!/usr/bin/env python


"""
[+] Usage: python.exe merge_shellcode.py [x86-32 shellcode input filename] [x86-64 shellcode input filename] [multi-bitness x86 shellcode output filename]

    [x86-32 shellcode input filename]             - Path to 32-bit x86 PIC file which is to be combined into a single-shot dual-mode payload
    [x86-64 shellcode input filename]             - Path to 64-bit x86 PIC file which is to be combined into a single-shot dual-mode payload
    [multi-bitness x86 shellcode output filename] - Path to multi-bitness x86 PIC file which will be saved to disk after merging (can be executed in both IA-32 and IA-32e mode)

    Example: python.exe merge_shellcode.py shellcode_x86.bin shellcode_x64.bin shellcode_multi.bin
"""


import sys
import struct


def main():
	try:
		if len(sys.argv) == 4:
			x86shellcodeinputfilename = sys.argv[1]
			x64shellcodeinputfilename = sys.argv[2]
			outputfilename = sys.argv[3]
		else:
			raise
	except:
		print("[-] Invalid args.")
		print(__doc__)
		sys.exit(0)

	x86shellcode = open(x86shellcodeinputfilename, "rb").read()
	x64shellcode = open(x64shellcodeinputfilename, "rb").read()
	file = open(outputfilename, "wb+")

	"""
	mode detection stub

	(32-bit)
	xor ecx, ecx ; set EFLAGS.ZF
	arpl cx, cx  ; clear EFLAGS.ZF
	jz rel32

	(64-bit)
	xor ecx, ecx ; set EFLAGS.ZF
	movsxd ecx, ecx
	jz rel32
	"""
	file.write(b'\x31\xC9\x63\xC9\x0F\x84')
	file.write(struct.pack('<I', len(x86shellcode)))
	file.write(x86shellcode)
	file.write(x64shellcode)

	file.close()

	print("[+] Merged x86-32 and x86-64 shellcode into multi-bitness x86 shellcode.")


if __name__ == '__main__':
	main()