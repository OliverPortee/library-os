#include "device/cgastr.h"

int main()
{
	CGA_Stream kout;
	for (int i = 0; i < 20; i++)
	{
		kout << "Hello World!" << ' ' << endl;	
	}

	kout.flush();

	return 0;
}
