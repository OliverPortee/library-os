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
mov rbx, [rbx_offset + rdi]
mov r12, [r12_offset + rdi]
mov r13, [r13_offset + rdi]
mov r14, [r14_offset + rdi]
mov r15, [r15_offset + rdi]
mov rbp, [rbp_offset + rdi]
mov rsp, [rsp_offset + rdi]
ret
; optional: load extended cpu state

; TOC_SWITCH: Context switch. Saves the current register values and replaces
;             them with values of the new "thread of control".
;
; C prototype: void toc_switch (struct toc* regs_now,
;                               struct toc* reg_then);

toc_switch:
mov [rbx_offset + rdi], rbx
mov [r12_offset + rdi], r12
mov [r13_offset + rdi], r13
mov [r14_offset + rdi], r14
mov [r15_offset + rdi], r15
mov [rbp_offset + rdi], rbp
mov [rsp_offset + rdi], rsp
; optional: save simd registers

mov rbx, [rbx_offset + rsi]
mov r12, [r12_offset + rsi]
mov r13, [r13_offset + rsi]
mov r14, [r14_offset + rsi]
mov r15, [r15_offset + rsi]
mov rbp, [rbp_offset + rsi]
mov rsp, [rsp_offset + rsi]
; optional: restore simd registers
ret
