/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L O C K E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Locker class implements a lock that can be used to protect critical   */
/* sections. However, the variable only indicates whether the critical       */
/* section is free. Potentially necessary waiting, and protection for        */
/* counting functionality, must be implemented elsewhere.                    */
/*****************************************************************************/

#ifndef __Locker_include__
#define __Locker_include__

#include "machine/cpu.h"
#include "device/cgastr.h"
#include "object/assert.h"

extern CPU cpu;
extern CGA_Stream kout;

class Locker {
private:
	Locker(const Locker &copy); // prevent copying
	bool available;

public: 
	Locker() {
		available = true;
	}

	inline void enter() {
		assert(available, "ERROR: multiple calls to enter()");
		available = false;
	}

	inline void retne() {
		assert(!available, "ERROR: multiple calls to retne()");
		available = true;
	}

	inline bool avail() {
		return available;
	}
};

#endif
