/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K I C K O F F                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Function to start a coroutine.                                            */
/* Since this function is not really called, but only jumped to by a clever  */
/* initialization of the stack of the coroutine, it must never terminate.    */
/* Otherwise a meaningless value would be interpreted as a return address    */
/* and the computer would crash.                                             */
/*****************************************************************************/

#ifndef __kickoff_h__
#define __kickoff_h__

#include "thread/coroutine.h"
#include "guard/guard.h"
#include "object/assert.h"

void kickoff(void* dummy1, void* dummy2, void* dummy3, void* dummy4,
             void* dummy5, void* dummy6, Coroutine* object) {
    assert(guard.empty(), "kickoff: guard is not empty");
    guard.retne();
    object->action();
    while (true) {
    }
}

#endif