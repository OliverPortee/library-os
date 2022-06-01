#include "machine/cpu.h"
#include "device/keyboard.h"
#include "user/appl.h"
#include "device/cgastr.h"
#include "thread/scheduler.h"
#include "thread/dispatch.h"
#include "user/task1.h"
#include "user/task2.h"



int main()
{
	cpu.enable_int();
	keyboard.plugin();

	kout << "main" << endl;

	scheduler.ready(task1);
	scheduler.ready(task2);
	scheduler.schedule();

	return 0;
}
