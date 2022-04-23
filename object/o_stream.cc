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

O_Stream &O_Stream::operator<<(unsigned char c)
{
    put((char)c);
    return *this;
}

O_Stream &O_Stream::operator<<(char c)
{
    put(c);
    return *this;
}

const char * const digits = "0123456789abcdef";

template<class T>
void format_natural_number(O_Stream& stream, T num, int base)
{
    // needs to fit 2^64 in binary plus null terminator
    const unsigned int length = 66;
    char buffer[length];
    unsigned int i = length - 1;
    buffer[i--] = '\0';
    while (num > 0) {
        buffer[i--] = digits[num % base];
        num /= base;
    }
    stream << buffer + i + 1;
}

template<class T>
void format_negative_with_minus(O_Stream& stream, T num, int base) {
    // needs to fit 2^64 in binary plus null terminator plus minus sign
    const unsigned int length = 67;
    char buffer[length];
    unsigned int i = length - 1;
    buffer[i--] = '\0';
    while (num < 0) {
        buffer[i--] = digits[-(num % base)];
        num /= base;
    }
    buffer[i--] = '-';
    stream << buffer + i + 1;
}


template<class T, class Unsigned>
void format(O_Stream& stream, T num, int base) {
    if (num > 0) {
        format_natural_number(stream, num, base);
    } else if (num < 0) {
        if (base == 10) {
            format_negative_with_minus(stream, num, base);
        } else {
            Unsigned new_num = *reinterpret_cast<Unsigned*>(&num);
            format_natural_number(stream, new_num, base);
        }
    } else {
        stream << '0';
    }
}

O_Stream &O_Stream::operator<<(unsigned short number)
{
    format<unsigned short, unsigned short>(*this, number, base);
    return *this;
}

O_Stream &O_Stream::operator<<(short number)
{
    format<short, unsigned short>(*this, number, base);
    return *this;
}

O_Stream &O_Stream::operator<<(unsigned int number)
{
    format<unsigned int, unsigned int>(*this, number, base);
    return *this;
}

O_Stream &O_Stream::operator<<(int number)
{
    format<int, unsigned int>(*this, number, base);
    return *this;
}

O_Stream &O_Stream::operator<<(unsigned long number)
{
    format<unsigned long, unsigned long>(*this, number, base);
    return *this;
}

O_Stream &O_Stream::operator<<(long number)
{
    format<long, unsigned long>(*this, number, base);
    return *this;
}

O_Stream& O_Stream::operator<<(void* pointer) {
    unsigned long num = *reinterpret_cast<unsigned long*>(&pointer);
    format<unsigned long, unsigned long>(*this, num, 16);
    return *this;
}

O_Stream &O_Stream::operator<<(const char *text)
{
    const char* pos = text;
    while (*pos != '\0') {
        put(*pos++);
    }
    return *this;
}

O_Stream& O_Stream::operator<<(O_Stream& (*fkt)(O_Stream&))
{
    return fkt(*this);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          M A N I P U L A T O R S                          */
/*                                                                           */
/*---------------------------------------------------------------------------*/

O_Stream &endl(O_Stream &os)
{
    os.put('\n');
    os.flush();
    return os;
}

O_Stream &flush(O_Stream &os)
{
    os.flush();
    return os;
}

O_Stream& bin(O_Stream& os) {
    os.base = 2;
    return os;
}

O_Stream& oct(O_Stream& os) {
    os.base = 8;
    return os;
}

O_Stream& dec(O_Stream& os) {
    os.base = 10;
    return os;
}

O_Stream& hex(O_Stream& os) {
    os.base = 16;
    return os;
}