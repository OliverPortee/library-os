/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S E M A P H O R E                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Guarded_Semaphore class implements the system call interface to the   */
/* Semaphore class.                                                          */
/*****************************************************************************/

#ifndef __Guarded_Semaphore_include__
#define __Guarded_Semaphore_include__

#include "meeting/semaphore.h"

class Guarded_Semaphore : Semaphore {
   private:
    Guarded_Semaphore(const Guarded_Semaphore &copy);  // prevent copying
   public:
    Guarded_Semaphore(int c);
    void p();
    void v();
    void wait();
    void signal();
};

#endif
