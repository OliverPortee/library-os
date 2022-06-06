/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             T H R E A D                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implements user interface of a thread.                                    */
/*****************************************************************************/

#ifndef __thread_include__
#define __thread_include__

#include "thread/entrant.h"

class Thread : public Entrant {
   private:
    Thread(const Thread &copy);  // prevent copying

   public:
	Thread(void* tos) : Entrant{tos} {}
};

#endif
