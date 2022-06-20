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

#include "thread/customer.h"

class Thread : public Customer {
   private:
    Thread(const Thread &copy);  // prevent copying

   public:
	Thread(void* tos) : Customer{tos} {}
};

#endif
