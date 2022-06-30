/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ K E Y B O A R D                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Guarded_Keyboard class provides the system call interface to the      */
/* keyboard.                                                                 */
/*****************************************************************************/

#ifndef __Guarded_Keyboard_include__
#define __Guarded_Keyboard_include__

#include "device/keyboard.h"

class Guarded_Keyboard : public Keyboard {
   private:
    Guarded_Keyboard(const Guarded_Keyboard &copy);  // prevent copying
   public:
    Guarded_Keyboard() {}
    Key getkey();
};

extern Guarded_Keyboard keyboard;

#endif
