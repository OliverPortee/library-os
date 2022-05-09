/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  G A T E                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Class of objects that handle interrupts.                                  */
/*****************************************************************************/

#ifndef __Gate_include__
#define __Gate_include__

class Gate : public Chain {
   private:
    bool _queued;

   public:
    virtual bool prologue() {}
    virtual void epilogue() {}
    void queue(bool q) { _queued = q; }
    bool queued() const { return _queued; }
};

#endif
