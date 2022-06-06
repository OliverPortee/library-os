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

char app_stack[65536];

Application::Application(void* tos) : Thread{tos} {}

void Application::action() { kout << "application" << endl; }