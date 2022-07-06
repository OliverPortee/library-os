/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 B E L L                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Bell is an abstract base class that allows the time-controlled triggering */
/* of an activity. For this purpose, it has an internal counter that is      */
/* managed by the Bellringer.                                                */
/*****************************************************************************/

#ifndef __Bell_include__
#define __Bell_include__

#include "object/assert.h"
#include "object/chain.h"

class Bell : public Chain {
   private:
    Bell(const Bell &copy);  // prevent copying

    int _value{};

   public:
    Bell() {}

    inline void wait(int value) {
        assert(value > 0, "Bell::wait with value <= 0");
        _value = value;
    }

    inline int wait() { return _value; }
    inline void tick() { --_value; }
    inline bool run_down() { return _value == 0; }
    virtual void ring() = 0;
};

#endif
