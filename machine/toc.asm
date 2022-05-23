;******************************************************************************
;* Operating-System Construction                                              *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                               T O C . A S M                                *
;*                                                                            *
;*----------------------------------------------------------------------------*
;*
;******************************************************************************

%include "machine/toc.inc"

; EXPORTED FUNCTIONS

[GLOBAL toc_switch]
[GLOBAL toc_go]

; FUNCTION IMPLEMENTATIONS

[SECTION .text]

; TOC_GO: Starts the very first process.
;
; C prototype: void toc_go(struct toc* regs);

toc_go:
; Add your code here 
mov rbx, [rdi + rbx_offset]
mov r12, [rdi + r12_offset]
mov r13, [rdi + r13_offset]
mov r14, [rdi + r14_offset]
mov r15, [rdi + r15_offset]
mov rbp, [rdi + rbp_offset]
mov rsp, [rdi + rsp_offset]
; optional load extended cpu state

; TOC_SWITCH: Context switch. Saves the current register values and replaces
;             them with values of the new "thread of control".
;
; C prototype: void toc_switch (struct toc* regs_now,
;                               struct toc* reg_then);

toc_switch:
; Add your code here
