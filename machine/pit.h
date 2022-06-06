/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#ifndef __pit_include__
#define __pit_include__

#include "machine/io_port.h"

class PIT {
private:
	PIT(const PIT &copy); // prevent copying

	IO_Port port{0x40};

	int us{};

public:
	PIT(int us);
	int interval() const;
	void interval(int us);
};

#endif
