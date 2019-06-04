#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void SwapList(struct Node**, struct Node*, struct Node*); //if any is head, not work yet

int main(){
	struct Node *head = NULL; 
  
    Push(&head, 7);
    struct Node *t = head; 
    Push(&head, 1);

    Push(&head, 3);
    struct Node *u = head;
    Push(&head, 2);



    puts("Created Linked List: \n"); 
    Printlist(head);

    SwapList(&head, u, t);
    puts("After swapping: \n");
    Printlist(head);

	return 0;
}

#if LINKED_LIST_TYPE == 1
	void SwapList(struct Node** head, struct Node* u, struct Node* t)
	{
		struct Node *prev_u, *prev_t, *tmp = *head;
		while(tmp->next != NULL){
			if (tmp->next == u)
				prev_u = tmp;
			if (tmp->next == t)
				prev_t = tmp;
			tmp = tmp->next;

		}
		prev_u->next = t;
		prev_t->next = u;
		tmp = u->next;
		u->next = t->next;
		t->next = tmp;
	}
#endif

#if LINKED_LIST_TYPE == 2
	void SwapList(struct Node** head, struct Node* u, struct Node* t)
	{
		if (u->next != NULL)
			u->next->prev = t;
		if (t->next != NULL)
			t->next->prev = u;
		if (t->prev != NULL)
			t->prev->next = u;
		else
			*head = u;
		if (u->prev != NULL)
			u->prev->next = t;
		else
			*head = t;
		
		struct Node *tmp;

		tmp = u->next;
		u->next = t->next;
		t->next = u->next;

		tmp = u->prev;
		u->prev = t-prev;
		t-prev = tmp;
	}
#endif

#if LINKED_LIST_TYPE == 3
	void SwapList(struct Node** head, struct Node* u, struct Node* t)
	{
		struct Node *prev_u, *prev_t, *tmp = *head;
		while(tmp->next != **head){
			if (tmp->next == u)
				prev_u = tmp;
			if (tmp->next == t)
				prev_t = tmp;
			tmp = tmp->next;
		}
		prev_u->next = t;
		prev_t->next = u;
		tmp = u->next;
		u->next = t->next;
		t->next = tmp;
	}
#endif