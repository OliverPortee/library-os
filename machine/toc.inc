;*****************************************************************************
;* Operating-System Construction                                             *
;*---------------------------------------------------------------------------*
;*                                                                           *
;*                                  T O C                                    *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Assembler variant of struct toc definition from toc.h                     *
;*                                                                           *
;* The register-name order must match that of struct toc (toc.h).            *
;*****************************************************************************

; STRUCTURES

; TOC: non-volatile registers of an x86-64 CPU (System V AMD64 ABI)

; The following definitions set rbx_offset to 0, r12_offset to 8, r13_offset
; to 16, and so on. This matches the offsets of elements rbx, r12, r13 etc.
; in struct toc (in bytes).

[ABSOLUTE 0]
rbx_offset: resq 1
r12_offset: resq 1
r13_offset: resq 1
r14_offset: resq 1
r15_offset: resq 1
rbp_offset: resq 1
rsp_offset: resq 1
fpu_offset: resb 108
