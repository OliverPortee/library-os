/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          C O R O U T I N E                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Represents the abstraction of a coroutine.                                */
/* In the constructor, we set up the initial context of the coroutine. go()  */
/* activates the first coroutine. All further coroutine switches should be   */
/* initiated by resume().                                                    */
/* To be able to save the context at a couroutine switch, every Coroutine    */
/* object contains a struct toc that stores the values of all non-volatile   */
/* registers.                                                                */
/*****************************************************************************/

#include "thread/coroutine.h"

#include "thread/kickoff.h"

// Functions that are implemented at C or assembler level must be declared as
// extern "C", because they do not conform to C++ name mangling.
extern "C" {
void toc_settle(struct toc *regs, void *tos,
                void (*kickoff)(void *, void *, void *, void *, void *, void *,
                                Coroutine *),
                void *object);

void toc_go(struct toc *regs);

void toc_switch(struct toc *regs_now, struct toc *regs_then);
}

Coroutine::Coroutine(void *tos) { toc_settle(&_toc, tos, kickoff, this); }

void Coroutine::go() { toc_go(&_toc); }

void Coroutine::resume(Coroutine &next) { toc_switch(&_toc, &next._toc); }