/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The "bell ringer" (Bellringer) is activated periodically and checks if    */
/* any "bells" (Bell objects) need to ring. The bells are in a list that the */
/* bellringer manages.                                                       */
/*****************************************************************************/

#ifndef __Bellringer_include__
#define __Bellringer_include__

#include "object/list.h"
#include "meeting/bell.h"

class Bellringer : public List {
private:
	Bellringer(const Bellringer &copy); // prevent copying
public:
	Bellringer() {}

	void check();
	void job(Bell* bell, int ticks);
	void cancel(Bell* bell);
};

extern Bellringer bellringer;

#endif
