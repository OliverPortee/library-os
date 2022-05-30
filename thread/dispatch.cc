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
#include "machine/cpu.h"
#include "device/cgastr.h"

Dispatcher::Dispatcher() {}

void Dispatcher::go(Coroutine& first) {
    if (active_coroutine != nullptr) {
        kout << "called Dispatcher.go twice" << endl;
        cpu.halt();
    }
    active_coroutine = &first;
    first.go();
}

void Dispatcher::dispatch(Coroutine& next) {
    if (active_coroutine == nullptr) {
        kout << "called Dispatcher.dispatch with no previous coroutine" << endl;
        cpu.halt();
    }
    Coroutine* tmp = active_coroutine;
    active_coroutine = &next;
    tmp->resume(next);
}

Coroutine* Dispatcher::active() const {
    return active_coroutine;
}