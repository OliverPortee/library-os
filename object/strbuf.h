/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       S T R I N G B U F F E R                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Stringbuffer class provides a buffer for collecting characters to be  */
/* printed to an output device, in our case the PC screen. The actual output */
/* occurs once the buffer is full, or when the user explicitly calls         */
/* flush().                                                                  */
/* As Stringbuffer is intended to be device independent, flush() is a        */
/* (pure) virtual method that must be defined by derived classes.            */
/*****************************************************************************/

#ifndef __strbuf_include__
#define __strbuf_include__

const unsigned int buf_size = 80;

class Stringbuffer {
private:
	Stringbuffer(const Stringbuffer &copy); // prevent copying

/* Add your code here */
protected:
    unsigned int next_free = 0;
    char buf[buf_size] = { 0 }; 

public:
	Stringbuffer(){}
	
	virtual void flush();
	void put(char c);
};

#endif
