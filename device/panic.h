/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Default interrupt handler.                                                */
/*****************************************************************************/

#ifndef __panic_include__
#define __panic_include__

#include "guard/gate.h"

class Panic : public Gate
{
private:
	Panic (const Panic &copy); // prevent copying
public:
	Panic () {}
	bool prologue(); 
};

extern Panic panic;

#endif
