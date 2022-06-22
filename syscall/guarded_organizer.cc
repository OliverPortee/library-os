/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ O R G A N I Z E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Guarded_Organizer implements the system call interface to the         */
/* Organizer.                                                                */
/*****************************************************************************/

#include "syscall/guarded_organizer.h"

#include "guard/secure.h"

Guarded_Organizer::Guarded_Organizer() {}

void Guarded_Organizer::ready(Thread& thread) {
    Secure secure;
    Organizer::ready(thread);
}

void Guarded_Organizer::exit() {
    Secure secure;
    Organizer::exit();
}

void Guarded_Organizer::kill(Thread& thread) {
    Secure secure;
    Organizer::kill(thread);
}

void Guarded_Organizer::resume() {
    Secure secure;
    Organizer::resume();
}

Guarded_Organizer organizer{};