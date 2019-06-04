#include <stdio.h>
#include <stdlib.h>

#define LINKED_LIST_TYPE 3//3: circle

#include "linkedList.h"

int NodeCount(struct Node *, struct Node *);

int main(){
	struct Node *head = NULL;
	struct Node *x;
	struct Node *t;
  
    Push(&head, 1);
    t = head; 
    Push(&head, 2); 
    Push(&head, 3); 
    Push(&head, 4);
    x = head;
    Push(&head, 5);
    printf("%d\n", NodeCount(x, t));
	return 0;
}

int NodeCount(struct Node *x, struct Node *t)
{
	int cnt = 0;
	struct Node *start = x;
	int i = 1;
	while (x != t){
		cnt++;
		x = x->next;
		if(x == start){
			printf("error: infinite loop\n");
		}
	}
	return cnt;
}