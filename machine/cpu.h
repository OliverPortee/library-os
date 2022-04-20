/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                   C P U                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* An abstraction for the CPU.                                               */
/* Currently allows enabling/disabling interrupts and halting the CPU.       */
/*****************************************************************************/

#ifndef __CPU_include__
#define __CPU_include__

// These functions are implemented in cpu.asm.
extern "C" void int_enable ();
extern "C" void int_disable ();
extern "C" void cpu_idle ();
extern "C" void cpu_halt ();

class CPU {
private:
	CPU(const CPU &copy); // prevent copying
public:
	CPU() {}
	// Allow (hardware) interrupts
	inline void enable_int() { int_enable(); }

	// Disallow/ignore interrupts
	inline void disable_int() { int_disable(); }

	// Enable interrupts and halt CPU until the next interrupt occurs
	inline void idle() { cpu_idle(); }

	// Halt CPU (forever)
	inline void halt() { cpu_halt(); }
};

#endif
