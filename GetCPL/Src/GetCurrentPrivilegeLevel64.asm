; ------------------------------------------------------------------------
; File: GetCurrentPrivilegeLevel64.asm
;
; Author: winterknife
;
; Description: x64 assembly routine to read the
; Machine Status Word (bits 0 through 15 of control register CR0) using
; the SMSW instruction and determine the Current Privilege Level (CPL)
; if the execution mode of the processor is protected mode
;
; Modifications:
;  2025-06-16	Created
;  2025-06-16	Updated
; ------------------------------------------------------------------------

; Start of .text segment
.CODE

; Align by 16 bytes
ALIGN 16

; Check the Current Privilege Level (CPL) of the processor
is_supervisor_mode PROC PUBLIC
	; Store the Machine Status Word (bits 0 through 15 of control register CR0) into AX register
	smsw ax       ; AX = CR0[15:0]

	; Check if CR0.PE flag is set
	; Protection Enable (bit 0 of CR0) enables protected mode when set and enables real-address mode when clear
	bt ax, 0h     ; EFLAGS.CF = Bit(AX, 0)
	jnc cleanup   ; if (EFLAGS.CF == 0) goto cleanup

	; Store the Code Segment (CS) register value in AX
	mov ax, cs    ; AX = CS

	; Check the CPL of the processor
	; Processor maintains an internal state called Current Privilege Level (CPL) which is defined as the privilege level of the currently executing code
	; CPL is used to determine whether certain operations are permitted or not
	; CPL is given by CS.RPL (bits 0 and 1)
	; Windows OS only uses CPL0 and CPL3
	and ax, 3h    ; AX = AX & 0x03
	jz supervisor ; if (EFLAGS.ZF == 1) goto supervisor
	xor ax, ax    ; AX = AX ^ AX = 0
	jmp cleanup   ; goto cleanup
supervisor:
	inc ax        ; AX = AX + 0x01

	; Cleanup
cleanup:
	; Return AX register value to the calling procedure
	ret           ; IP = [SP] and SP = SP + 0x02
is_supervisor_mode ENDP

; End of MASM source
END