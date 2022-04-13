#include "device/cgastr.h"
#include "machine/cgascr.h"
#include "object/o_stream.h"

int main()
{
	for (int i = 0; i < 20; i++)
	{
		kout << "Hello World!" << ' ' << endl;	
	}

	kout << (void *)0xff77 << endl;
	kout << 0 << endl;
	
	kout << "short: " << (short) -32768 << endl;
	kout << "short: " << (short)  32767 << endl;
	kout << "unsigned short: " << (unsigned short) 65535 << endl;
	kout << "int: " << (int) -2147483648 << endl;
	kout << "int: " << (int)  2147483647 << endl;
	kout << "unsigned int: " << (unsigned int) 4294967295 << endl;
	kout << "long: " << (long) -9223372036854775808 << endl;
	kout << "long: " << (long)  9223372036854775807 << endl;
	kout << "unsigned long: " << (unsigned long) 18446744073709551615 << endl;

	kout.base = 16;

	kout << 0 << endl;
	kout << "short: " << (short) -32768 << endl;
	kout << "short: " << (short)  32767 << endl;
	kout << "unsigned short: " << (unsigned short) 65535 << endl;
	kout << "int: " << (int) -2147483648 << endl;
	kout << "int: " << (int)  2147483647 << endl;
	kout << "unsigned int: " << (unsigned int) 4294967295 << endl;
	kout << "long: " << (long) -9223372036854775808 << endl;
	kout << "long: " << (long)  9223372036854775807 << endl;
	kout << "unsigned long: " << (unsigned long) 18446744073709551615 << endl;

	kout << "aslfjad"; // gets flushed automatically

	return 0;
}
