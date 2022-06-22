/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Application class defines the (only) application for OOStuBS.         */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"

#include "syscall/guarded_organizer.h"
#include "user/task1.h"
#include "user/task2.h"

char app_stack[65536];

Application::Application() : Thread{app_stack + sizeof(app_stack)} {}

void Application::action() {
    organizer.ready(task1);
    organizer.ready(task2);
}

Application app{};