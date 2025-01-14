; ------------------------------------------------------------------------
; File: ReadMsw64.asm
;
; Author: winterknife
;
; Description: x64 assembly routine to read the
; Machine Status Word (bits 0 through 15 of control register CR0) using
; the SMSW instruction
;
; Modifications:
;  2025-01-09	Created
;  2025-01-14	Updated
; ------------------------------------------------------------------------

; Start of .text segment
.CODE

; Align by 16 bytes
ALIGN 16

; Check if segment-level protection is enabled
is_protected_mode_enabled PROC PUBLIC
	; Store the Machine Status Word (bits 0 through 15 of control register CR0) into AX register
	smsw ax       ; AX = CR0[15:0]

	; Get CR0.PE flag
	and ax, 0001h ; AX = AX & 0x0001

	; Return AX register value to the calling procedure
	ret           ; IP = [SP] and SP = SP + 0x08
is_protected_mode_enabled ENDP

; End of MASM source
END