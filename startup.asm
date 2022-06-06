;******************************************************************************
;* Operating-System Construction                                              *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                        S T A R T U P . A S M                               *
;*                                                                            *
;*----------------------------------------------------------------------------*
;* The 'startup' function is the entry point for the whole system. Switching  *
;* to 32-bit Protected Mode has already been done (by a boot loader that runs *
;* before). Here we prepare everything to be able to start running C++ code   *
;* in 64-bit Long Mode as quickly as possible.                                *
;******************************************************************************

;
;   Constants
;

; stack for the main function
STACKSIZE: equ 65536

; video memory base address
CGA: equ 0xB8000

; 256 GB maximum RAM size for page table
MAX_MEM: equ 254

; Multiboot constants
MULTIBOOT_PAGE_ALIGN     equ   1<<0
MULTIBOOT_MEMORY_INFO    equ   1<<1

; magic number for Multiboot
MULTIBOOT_HEADER_MAGIC   equ   0x1badb002

; Multiboot flags (ELF specific!)
MULTIBOOT_HEADER_FLAGS   equ   MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
MULTIBOOT_HEADER_CHKSUM  equ   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
MULTIBOOT_EAX_MAGIC      equ   0x2badb002

; memory for the page table

[GLOBAL pagetable_start]
pagetable_start:  equ 0x103000

[GLOBAL pagetable_end]
pagetable_end:  equ 0x200000

;
;   System
;

; functions provided by us
[GLOBAL startup]
[GLOBAL idt]
[GLOBAL __cxa_pure_virtual]
[GLOBAL _ZdlPv]
[GLOBAL _ZdlPvj]
[GLOBAL _ZdlPvm]

; functions from the C parts of the system
[EXTERN main]
[EXTERN guardian]

; addresses provided by the compiler
[EXTERN ___BSS_START__]
[EXTERN ___BSS_END__]
[EXTERN __init_array_start]
[EXTERN __init_array_end]
[EXTERN __fini_array_start]
[EXTERN __fini_array_end]

[SECTION .text]

;
;   system start, part 1 (in 32-bit Protected Mode)
;
;   GDT and page-table initialization, and switch to 64-bit Long Mode
;

[BITS 32]

	jmp    startup  ; jump over Multiboot header
	align  4        ; 32-bit alignment for GRUB

;
;   Multiboot header for starting with GRUB or QEMU (w/o BIOS)
;

	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_HEADER_CHKSUM
	dd 0 ; header_addr (gets ignored)
	dd 0 ; load_addr (gets ignored)
	dd 0 ; load_end_addr (gets ignored)
	dd 0 ; bss_end_addr (gets ignored)
	dd 0 ; entry_addr (gets ignored)
	dd 0 ; mode_type (gets ignored)
	dd 0 ; width (gets ignored)
	dd 0 ; height (gets ignored)
	dd 0 ; depth (gets ignored)

;
;  GRUB entry point
;

startup:
	cld              ; GCC-compiled code expects the direction flag to be 0
	cli              ; disable interrupts
	lgdt   [gdt_80]  ; set new segment descriptors

	; global data segment
	mov    eax, 3 * 0x8
	mov    ds, ax
	mov    es, ax
	mov    fs, ax
	mov    gs, ax

	; define stack
	mov    ss, ax
	mov    esp, init_stack+STACKSIZE

;
;  Switch to 64-bit Long Mode
;

init_longmode:
	; activate address extension (PAE)
	mov    eax, cr4
	or     eax, 1 << 5
	mov    cr4, eax

	; create page table (mandatory)
	call   setup_paging

	; activate Long Mode (for now in compatibility mode)
	mov    ecx, 0x0C0000080 ; select EFER (Extended Feature Enable Register)
	rdmsr
	or     eax, 1 << 8 ; LME (Long Mode Enable)
	wrmsr

	; activate paging
	mov    eax, cr0
	or     eax, 1 << 31
	mov    cr0, eax

	; jump to 64-bit code segment -> full activation of Long Mode
	jmp    2 * 0x8 : longmode_start

;
;   Generation of a (provisional) page table with a page size of 2 MB, which
;   maps the first MAX_MEM GB directly to physical memory. Currently, the
;   system must not have more memory.
;   All of this is necessary because Long Mode mandates a working page table.
;

setup_paging:
	; PML4 (Page Map Level 4 / 1st level)
	mov    eax, pdp
	or     eax, 0xf
	mov    dword [pml4+0], eax
	mov    dword [pml4+4], 0

	; PDPE (Page Directory Pointer Entry / 2nd level) for currently 16 GB
	mov    eax, pd
	or     eax, 0x7           ; address of the first table (3rd level) with flags
	mov    ecx, 0
fill_tables2:
	cmp    ecx, MAX_MEM       ; reference MAX_MEM tables
	je     fill_tables2_done
	mov    dword [pdp + 8*ecx + 0], eax
	mov    dword [pdp + 8*ecx + 4], 0
	add    eax, 0x1000        ; tables are sized 4 kB each
	inc    ecx
	ja     fill_tables2
fill_tables2_done:

	; PDE (Page Directory Entry / 3rd level)
	mov    eax, 0x0 | 0x87    ; start-address bytes 0..3 (=0) + flags
	mov    ebx, 0             ; start-address bytes 4..7 (=0)
	mov    ecx, 0
fill_tables3:
	cmp    ecx, 512*MAX_MEM   ; fill MAX_MEM tables with 512 entries each
	je     fill_tables3_done
	mov    dword [pd + 8*ecx + 0], eax ; low bytes
	mov    dword [pd + 8*ecx + 4], ebx ; high bytes
	add    eax, 0x200000      ; 2 MB per page
	adc    ebx, 0             ; overflow? -> increment higher-order half of the address
	inc    ecx
	ja     fill_tables3
fill_tables3_done:

	; set base pointer to PML4
	mov    eax, pml4
	mov    cr3, eax
	ret

;
;   system start, part 2 (in 64-bit Long Mode)
;
;   This code clears the BSS segment and initializes IDT and PICs. Then the
;   constructors of global C++ objects are called, and finally main() is run.
;

longmode_start:
[BITS 64]
	; clear BSS
	mov    rdi, ___BSS_START__
clear_bss:
	mov    byte [rdi], 0
	inc    rdi
	cmp    rdi, ___BSS_END__
	jne    clear_bss

	; initialize IDT and PICs
	call   setup_idt
	call   reprogram_pics
	call   setup_cursor

	fninit         ; activate FPU

	; init SSE
	;mov rax, cr0
	;and rax, ~(1 << 2)	;clear coprocessor emulation CR0.EM
	;or rax, 1 << 1		;set coprocessor monitoring  CR0.MP
	;mov cr0, rax
	;mov rax, cr4
	;or rax, 3 << 9		;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
	;mov cr4, rax

	call   _init   ; call constructors of global objects
	call   main    ; call the OS kernel's C / C++ part
	call   _fini   ; call destructors
	cli            ; Usually we should not get here.
	hlt

;
;   Interrupt handling
;

; template for header for each interrupt-handling routine
%macro wrapper 1
wrapper_%1:
	push   rbp
	mov    rbp, rsp
	push   rax
	mov    al, %1
	jmp    wrapper_body
%endmacro

; automatic generation of 256 interrupt-handling routines, based on above macro
%assign i 0
%rep 256
wrapper i
%assign i i+1
%endrep

; common handler body
wrapper_body:
	; GCC expects the direction flag to be 0
	cld
	; save volatile registers
	push   rcx
	push   rdx
	push   rdi
	push   rsi
	push   r8
	push   r9
	push   r10
	push   r11

	; the generated wrapper only gives us 8 bits, mask the rest
	and    rax, 0xff

	; pass interrupt number as the first parameter
	mov    rdi, rax
	call   guardian

	; restore volatile registers
	pop    r11
	pop    r10
	pop    r9
	pop    r8
	pop    rsi
	pop    rdi
	pop    rdx
	pop    rcx

	; ... also those from the wrapper
	pop    rax
	pop    rbp

	; done
	iretq

;
; Relocating of IDT entries and setting IDTR
;

setup_idt:
	mov    rax, wrapper_0

	; bits 0..15 -> ax, 16..31 -> bx, 32..64 -> edx
	mov    rbx, rax
	mov    rdx, rax
	shr    rdx, 32
	shr    rbx, 16

	mov    r10, idt   ; pointer to the actual interrupt gate
	mov    rcx, 255   ; counter
.loop:
	add    [r10+0], ax
	adc    [r10+6], bx
	adc    [r10+8], edx
	add    r10, 16
	dec    rcx
	jge    .loop

	lidt   [idt_descr]
	ret

;
; make cursor blink (GRUB disables this)
;

setup_cursor:
	mov al, 0x0a
	mov dx, 0x3d4
	out dx, al
	call delay
	mov dx, 0x3d5
	in al, dx
	call delay
	and al, 0xc0
	or al, 14
	out dx, al
	call delay
	mov al, 0x0b
	mov dx, 0x3d4
	out dx, al
	call delay
	mov dx, 0x3d5
	in al, dx
	call delay
	and al, 0xe0
	or al, 15
	out dx, al
	ret

;
; Reprogram the PICs (programmable interrupt controllers) to have all 15
; hardware interrupts in sequence in the IDT.
;

reprogram_pics:
	mov    al, 0x11   ; ICW1: 8086 mode with ICW4
	out    0x20, al
	call   delay
	out    0xa0, al
	call   delay
	mov    al, 0x20   ; ICW2 master: IRQ # offset (32)
	out    0x21, al
	call   delay
	mov    al, 0x28   ; ICW2 slave: IRQ # offset (40)
	out    0xa1, al
	call   delay
	mov    al, 0x04   ; ICW3 master: slaves with IRQs
	out    0x21, al
	call   delay
	mov    al, 0x02   ; ICW3 slave: connected to master's IRQ2
	out    0xa1, al
	call   delay
	mov    al, 0x03   ; ICW4: 8086 mode and automatic EOI
	out    0x21, al
	call   delay
	out    0xa1, al
	call   delay

	mov    al, 0xff   ; Mask/disable hardware interrupts
	out    0xa1, al   ; in the PICs. Only interrupt #2, which
	call   delay      ; serves for cascading both PICs, is
	mov    al, 0xfb   ; allowed.
	out    0x21, al

	ret

;
; Run constructors of global objects
;

_init:
	mov    rbx, __init_array_start
_init_loop:
	cmp    rbx, __init_array_end
	je     _init_done
	mov    rax, [rbx]
	call   rax
	add    rbx, 8
	ja     _init_loop
_init_done:
	ret

;
; Run destructors of global objects
;

_fini:
	mov    rbx, __fini_array_start
_fini_loop:
	cmp    rbx, __fini_array_end
	je     _fini_done
	mov    rax, [rbx]
	call   rax
	add    rbx, 8
	ja     _fini_loop
_fini_done:
	ret

;
; Short delay for in/out instructions
;

delay:
	jmp    .L2
.L2:
	ret

;
; Functions for the C++ compiler. These labels must be defined for the linker;
; since OOStuBS does not release/free any memory, they may be empty, however.
;

__cxa_pure_virtual: ; a "virtual" method without implementation was called
_ZdlPv:             ; void operator delete(void*)
_ZdlPvj:            ; void operator delete(void*, unsigned int) for g++ 6.x
_ZdlPvm:            ; void operator delete(void*, unsigned long) for g++ 6.x
	ret

[SECTION .data]

;
; Segment descriptors
;

gdt:
	dw  0,0,0,0   ; NULL descriptor

	; 32-bit code segment descriptor
	dw  0xFFFF    ; 4Gb - (0x100000*0x1000 = 4Gb)
	dw  0x0000    ; base address=0
	dw  0x9A00    ; code read/exec
	dw  0x00CF    ; granularity=4096, 386 (+5th nibble of limit)

	; 64-bit code segment descriptor
	dw  0xFFFF    ; 4Gb - (0x100000*0x1000 = 4Gb)
	dw  0x0000    ; base address=0
	dw  0x9A00    ; code read/exec
	dw  0x00AF    ; granularity=4096, 386 (+5th nibble of limit), Long-Mode

	; data segment descriptor
	dw  0xFFFF    ; 4Gb - (0x100000*0x1000 = 4Gb)
	dw  0x0000    ; base address=0
	dw  0x9200    ; data read/write
	dw  0x00CF    ; granularity=4096, 386 (+5th nibble of limit)

gdt_80:
	dw  4*8 - 1   ; GDT limit=24, 4 GDT entries - 1
	dq  gdt       ; GDT address

;
; Interrupt descriptor table with 256 entries
;

idt:
%macro idt_entry 1
	dw  (wrapper_%1 - wrapper_0) & 0xffff ; offset 0 .. 15
	dw  0x0000 | 0x8 * 2 ; selector points to 64-bit code segment selector (GDT)
	dw  0x8e00 ; 8 -> interrupt is present, e -> 80386 32-bit interrupt gate
	dw  ((wrapper_%1 - wrapper_0) & 0xffff0000) >> 16 ; offset 16 .. 31
	dd  ((wrapper_%1 - wrapper_0) & 0xffffffff00000000) >> 32 ; offset 32..63
	dd  0x00000000 ; reserved
%endmacro

%assign i 0
%rep 256
idt_entry i
%assign i i+1
%endrep

idt_descr:
	dw  256*8 - 1    ; 256 entries
	dq idt

[SECTION .bss]

[GLOBAL MULTIBOOT_FLAGS]
[GLOBAL MULTIBOOT_LOWER_MEM]
[GLOBAL MULTIBOOT_UPPER_MEM]
[GLOBAL MULTIBOOT_BOOTDEVICE]
[GLOBAL MULTIBOOT_CMDLINE]
[GLOBAL MULTIBOOT_MODULES_COUNT]
[GLOBAL MULTIBOOT_MODULES_ADDRESS]

MULTIBOOT_FLAGS:            resd 1
MULTIBOOT_LOWER_MEM:        resd 1
MULTIBOOT_UPPER_MEM:        resd 1
MULTIBOOT_BOOTDEVICE:       resd 1
MULTIBOOT_CMDLINE:          resd 1
MULTIBOOT_MODULES_COUNT:    resd 1
MULTIBOOT_MODULES_ADDRESS:  resd 1

global init_stack:data (init_stack.end - init_stack)
init_stack:
	resb STACKSIZE
.end:

[SECTION .global_pagetable]

[GLOBAL pml4]
[GLOBAL pdp]
[GLOBAL pd]

pml4:
	resb   4096
	alignb 4096

pdp:
	resb   MAX_MEM*8
	alignb 4096

pd:
	resb   MAX_MEM*4096
