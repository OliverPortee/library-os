/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Using this class, we can synchronize activities with a critical section   */
/* with interrupt handlers that also access this critical section. This      */
/* synchronization takes place along the prologue/epilogue model.            */
/*****************************************************************************/

#ifndef __Guard_include__
#define __Guard_include__

/* Add your code here */ 

class Guard : public Locker {
private:
	Guard (const Guard &copy); // prevent copying
public:
	Guard () {}
/* Add your code here */ 
};

#endif
