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

; TOC_SWITCH: Context switch. Saves the current register values and replaces
;             them with values of the new "thread of control".
;
; C prototype: void toc_switch (struct toc* regs_now,
;                               struct toc* reg_then);

toc_switch:
mov [rdi + rbx_offset], rbx
mov [rdi + r12_offset], r12
mov [rdi + r13_offset], r13
mov [rdi + r14_offset], r14
mov [rdi + r15_offset], r15
mov [rdi + rbp_offset], rbp
mov [rdi + rsp_offset], rsp
; optional: save simd registers

mov rbx, [rsi + rbx_offset]
mov r12, [rsi + r12_offset]
mov r13, [rsi + r13_offset]
mov r14, [rsi + r14_offset]
mov r15, [rsi + r15_offset]
mov rbp, [rsi + rbp_offset]
mov rsp, [rsi + rsp_offset]
; optional: restore simd registers