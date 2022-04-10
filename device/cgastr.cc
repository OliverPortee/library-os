/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C G A _ S T R E A M                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The CGA_Stream class allows to print different data types as text strings */
/* to a PC's CGA screen.                                                     */
/* For attributes/colors and cursor positioning use the methods of class     */
/* CGA_Screen.                                                               */
/*****************************************************************************/

#include "device/cgastr.h"

/* Add your code here */ 
void CGA_Stream::flush() {

    char attrib = 0x0f;                 // defines fore- and background colour, 0x0f corresponds to white on black
    char *pos = (char *)0xb8000;

    for (unsigned int i = 0; i < next_free; i++)
    {
        *pos = buf[i];
        *(pos + 1) = attrib;
        pos += 2;
    }
    
    next_free = 0;
}