/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 T O C                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The toc struct is used to save the values of the non-volatile registers   */
/* in case of a context switch.                                              */
/* With the System V AMD64 ABI the GNU C compiler uses, RBP, RBX and R12 to  */
/* R15 are non-volatile registers that must be saved by hand at a context    */
/* switch. Additionally there are 108 bytes of non-volatile extended CPU     */
/* state that are only important if we use components like the FPU or SIMD   */
/* instructions.                                                             */
/*                                                                           */
/* Careful: For accessing struct toc elements from an assembler function, we */
/* define names for the necessary offsets from the struct's start in the     */
/* file toc.inc. To access the correct elements, definitions in toc.h and    */
/* toc.inc must match exactly. If you modify toc.h, you must also modify     */
/* toc.inc (and vice versa.)                                                 */
/*****************************************************************************/

#ifndef __toc_include__
#define __toc_include__

// TOC: ("thread of control")
//
struct toc {
	void *rbx;
	void *r12;
	void *r13;
	void *r14;
	void *r15;
	void *rbp;
	void *rsp;
	char fpu[108]; // optional: 108 bytes extended CPU state (MMX, SSE, ...)
};

#endif
