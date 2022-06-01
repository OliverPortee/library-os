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

#include "device/cgastr.h"
#include "guard/secure.h"
#include "machine/cpu.h"
#include "device/cgastr.h"
#include "user/task1.h"
#include "thread/dispatch.h"
#include "thread/entrant.h"

char app_stack[65536];

Application::Application(void* tos) : Entrant{tos} {}

void Application::action() {
    kout << "application" << endl;
}