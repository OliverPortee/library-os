/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          D I S P A T C H E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Dispatcher implementation.                                                */
/* The Dispatcher maintains the life pointer that points to the currently    */
/* active coroutine. go() initializes the life pointer and starts the first  */
/* coroutine, all further context switches are triggered by dispatch().      */
/* active() returns the life pointer.                                        */
/*****************************************************************************/

#include "thread/dispatch.h"

#include "guard/secure.h"
#include "object/assert.h"

Dispatcher::Dispatcher() {}

void Dispatcher::go(Coroutine& first) {
    assert(active_coroutine == nullptr, "called Dispatcher.go twice");
    active_coroutine = &first;
    active_coroutine->go();
}

void Dispatcher::dispatch(Coroutine& next) {
    assert(active_coroutine != nullptr,
           "called Dispatcher.dispatch with no previous coroutine");
    Coroutine* tmp = active_coroutine;
    active_coroutine = &next;
    tmp->resume(next);
}

Coroutine* Dispatcher::active() const { return active_coroutine; }

Dispatcher dispatcher{};