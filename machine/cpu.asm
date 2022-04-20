;*****************************************************************************
;* Operating-System Construction                                             *
;*---------------------------------------------------------------------------*
;*                                                                           *
;*                                   C P U                                   *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* This assembler module implements functionality from class CPU.            *
;*****************************************************************************

; EXPORTED FUNCTIONS

[GLOBAL int_enable]
[GLOBAL int_disable]
[GLOBAL cpu_idle]
[GLOBAL cpu_halt]

; IMPLEMENTATION

[SECTION .text]

; INT_ENABLE: Allow (hardware) interrupts
;
;       C prototype: void int_enable ();

int_enable:
	sti
	ret

; INT_DISABLE: Disallow/ignore interrupts
;
;       C prototype: void int_disable ();

int_disable:
	cli
	ret

; CPU_IDLE : Enable interrupts and halt CPU until the next interrupt occurs
;
;       C prototype: void cpu_idle (void)

cpu_idle:
	sti ; The STI / HLT sequence is executed atomically!
	hlt
	ret

; CPU_HALT : Halt CPU (forever)
;
;       C prototype: void cpu_halt (void)

cpu_halt:
	cli
	hlt
