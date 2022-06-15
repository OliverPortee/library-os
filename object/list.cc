/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L I S T                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung einer einfach verketteten Liste.                          */
/*****************************************************************************/

#include "object/list.h"

// INSERT_FIRST: Inserts the new_item at the beginning of the list.
void List::insert_first(Chain *new_item)
{
	if (head) { // Is the list empty?
		new_item->next = head;
		head = new_item;
	} else { // The list is empty. We can simply instead append at the "end".
		enqueue(new_item);
	}
}

// INSERT_AFTER: Inserts the new_item after the old_item element in the
//               list.
void List::insert_after(Chain *old_item, Chain *new_item)
{
	new_item->next = old_item->next;
	old_item->next = new_item;
}
