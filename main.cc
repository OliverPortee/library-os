#include "machine/cpu.h"
#include "device/keyboard.h"
#include "user/appl.h"
#include "device/cgastr.h"

int main()
{
	cpu.enable_int();
	keyboard.plugin();

	kout << "main" << endl;

	app.go();

	return 0;
}
