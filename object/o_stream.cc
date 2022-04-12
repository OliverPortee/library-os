/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The O_Stream class defines the << operator for several pre-defined data   */
/* types and thereby realizes output functionality similar to C++'s iostream */
/* library. By default, this class supports printing characters, strings and */
/* integer numbers of various bit sizes. Another << operator allows to use   */
/* so-called 'manipulators'.                                                 */
/*                                                                           */
/* Besides class O_Stream this file also defines the manipulators hex, dec,  */
/* oct and bin for choosing the basis in number representations, and endl    */
/* for implementing an (implicitly flushing) line termination.               */
/*****************************************************************************/

#include "object/o_stream.h"

/* Add your code here */ 

// characters
O_Stream& O_Stream::operator<<(unsigned char c) {
    put((char) c);
    return *this;
}	

O_Stream& O_Stream::operator<<(char c) {
    put(c);
    return *this;
}

// numbers
O_Stream& O_Stream::operator<<(unsigned short number) {

}

O_Stream& O_Stream::operator<<(short number) {

}

O_Stream& O_Stream::operator<<(unsigned int number) {

}

O_Stream& O_Stream::operator<<(int number) {

}

O_Stream& O_Stream::operator<<(unsigned long number) {

}

O_Stream& O_Stream::operator<<(long number) {

}

O_Stream& O_Stream::operator<<(void* pointer) {

}

// text is null terminated
O_Stream& O_Stream::operator<<(char* text) {
    char c = *text;
    while(c != '\0') {
        put(c);
        text += 1;
        c = *text;
    }
    return *this;
}	

O_Stream& O_Stream::operator<< (O_Stream& (*fkt) (O_Stream&)) {
    fkt(*this);
    return *this;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          M A N I P U L A T O R S                          */
/*                                                                           */
/*---------------------------------------------------------------------------*/

O_Stream& endl (O_Stream& os) {
    os.put('\n');
    return os;
}