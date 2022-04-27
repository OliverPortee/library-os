/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Application class defines the (only) application for OOStuBS.         */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "device/cgastr.h"
/* Add your code here */ 
#include "machine/cpu.h"
#include "machine/pic.h"

/* GLOBAL VARIABLES */

extern CGA_Stream kout;
/* Add your code here */ 
 
void Application::action()
{
/* Add your code here */
    int x, y;
    kout.getpos(x,y);

    while (true) {
        //cpu.disable_int();

        kout.setpos(x, y);
        kout << "some longer sample text" << endl
             << flush;

        //cpu.enable_int();
    }
}

Application app;