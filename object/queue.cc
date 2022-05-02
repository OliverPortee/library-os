/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Q U E U E                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementation of a singly-linked list of Chain objects. enqueue()        */
/* inserts a new element at the end of the list, dequeue() removes the first */
/* element, and remove() remove the element indicated by its argument.       */
/* Initially, the queue is empty.                                            */
/*                                                                           */
/* The implementation is a little bit tricky (see exercises). tail does not, */
/* as usual, point to the last element of the list, but to the next pointer  */
/* of this last element (or to the head pointer of the list, if it is still  */
/* empty). This allows us to implement the enqueue() operation without a     */
/* conditional distinguishing the empty from the non-empty case. However,    */
/* when removing elements, we cannot do without this conditional.            */
/*****************************************************************************/

#include "object/queue.h"

// ENQUEUE: Append the Chain object at the end of the list.

void Queue::enqueue(Chain *item)
{
	item->next = 0; // The new element has no successor yet.
	*tail = item;   // Append at the end of the list
	tail = &(item->next); // and update the tail pointer.
}

// DEQUEUE: Returns the list's first element and removes it from the list.
//          If the list does not contain any elements, it returns a nullptr.

Chain *Queue::dequeue()
{
	Chain *item;

	item = head; // The head pointer denotes the first element  
	if (item) {  // or contains a nullptr if the list is empty.
		head = item->next; // Unlink the first element from the list.
		if (!head)         // If the list is now empty, we must make sure
			tail = &head;  // the tail pointer points to head again.
		else               // Otherwise, invalidate the pointer
			item->next = 0;// to this element's successor.
	}
	return item;
}

// REMOVE: Searches the supplied Chain element and removes it.

void Queue::remove(Chain *item)
{
	Chain *cur;

	if (head) {
		cur = head;      // Search starts at the list's head.
		if (item == cur) // If the first element is the sought-after,
			dequeue();   // dequeue() suffices for removal.
		else {
			// Search until we reach the list's end, or the next element is
			// the one we are looking for.
			while (cur->next && item != cur->next) {
				cur = cur->next;
			}

			if (cur->next) {
				cur->next = item->next; // unlink element
				item->next = 0; // invalidate next ptr

				// If cur has no successor,
				if (!cur->next)
					// we need to update tail.
					tail = &(cur->next);
			}
		}
	}
}
