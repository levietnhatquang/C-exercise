#include <stdlib.h> 
#include <stdio.h>

struct Node
{ 
	int item;
	struct Node *next; 
}; 

int list_element_num(struct Node *node);

void main(int argc, char *argv[]){ 	
	int i;
	int N = atoi(argv[1]);
	int M = atoi(argv[2]) ;
	struct Node *t = (struct Node *)malloc(sizeof(struct Node));
	struct Node *x = t;
	t->item = 1;
	t->next = t;
	for (i = 2; i <= N; i++)
	{
		x = (x->next = malloc(sizeof *x));
		x->item = i;
		x->next = t;
	}
	while (x != x->next){ 
		for (i = 1; i < M; i++) 
			x = x->next;
		printf("Number of elecment in the list: %d\n", list_element_num(x));
		x->next = x->next->next; 
		N--;
	}
}

int list_element_num(struct Node *node)
{
	int counter = 0;
	for(struct Node *tmp = node; tmp->next != node; tmp = tmp->next)
		counter++;
	return counter;
}