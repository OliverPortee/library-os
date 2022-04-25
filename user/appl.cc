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

/* GLOBAL VARIABLES */

extern CGA_Stream kout;
/* Add your code here */ 
 
void Application::action()
{
/* Add your code here */
    CPU cpu{};
    int x, y;
    kout.getpos(x,y);

    while (true) {
        kout.setpos(x, y);
        kout << "sampletext";
        
        /*
        for (int i = 0; i < 40; i++)
        {
            kout.show(x+i, y, 'a', 0x0f);
        }
        */  
    }
}
