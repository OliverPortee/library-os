/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        G U A R D E D _ B U Z Z E R                        */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Guarded_Buzzer class implements the system call interface to the      */
/* Buzzer class.                                                             */
/*****************************************************************************/

#include "syscall/guarded_buzzer.h"
#include "guard/secure.h"

Guarded_Buzzer::Guarded_Buzzer() {}

Guarded_Buzzer::~Guarded_Buzzer() {
    Secure secure;
    this->Buzzer::~Buzzer();
}

void Guarded_Buzzer::set(int ms) {
    Secure secure;
    Buzzer::set(ms);
}

void Guarded_Buzzer::sleep() {
    Secure secure;
    Buzzer::sleep();
}
