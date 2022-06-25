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

/* Add your code here */
#include "syscall/guarded_keyboard.h"
#include "device/keyboard.h"
#include "guard/secure.h"

Key Guarded_Keyboard::getkey() {
    Secure secure;
    return Keyboard::getkey();
}
