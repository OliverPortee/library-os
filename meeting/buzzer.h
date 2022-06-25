/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* An "alarm clock" is a synchronization object that allows one or more      */
/* threads to put themselves to sleep for a specified time.                  */
/*****************************************************************************/

#ifndef __Buzzer_include__
#define __Buzzer_include__

#include "meeting/bell.h"
#include "meeting/waitingroom.h"

class Buzzer : public Waitingroom, public Bell {
   private:
    Buzzer(const Buzzer &copy);  // prevent copying

   public:
    Buzzer() = default;
    virtual ~Buzzer();
    virtual void ring();
    void set(int ms);
    void sleep();
};

#endif
