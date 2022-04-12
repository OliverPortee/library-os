#include "device/cgastr.h"

int main()
{
	CGA_Stream kout;
	for (int i = 0; i < 20; i++)
	{
		kout << 'H'
			 << 'e'
			 << 'l'
			 << 'l'
			 << 'o'
			 << ' '
			 << 'W'
			 << 'o'
			 << 'r'
			 << 'l'
			 << 'd'
			 << '!'
			 << ' ';	
	}

	kout.flush();

	return 0;
}
