#include "machine/cpu.h"
#include "device/keyboard.h"
#include "user/appl.h"
#include "device/cgastr.h"
#include "thread/dispatch.h"

int main()
{
	cpu.enable_int();
	keyboard.plugin();

	kout << "main" << endl;

	dispatcher.go(app);

	return 0;
}
