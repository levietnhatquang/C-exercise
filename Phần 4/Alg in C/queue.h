#define QUEUE_TYPE 2 // array: 1 - linkedlist: 2

#if QUEUE_TYPE == 1
	#define __QUEUE_ARRAY_BASE__
	struct Queue 
	{ 
	    int front, rear, size; 
	    unsigned capacity; 
	    int* array; 
	};
#endif

#if QUEUE_TYPE == 2
	#define __QUEUE_LINKED_LIST_BASE__
	//#include "linkedList.h"
	struct Queue 
	{ 
	    int size; 
	    unsigned capacity; 
	    struct Node *head; 
	}; 

#endif

	struct Queue* createQueue(unsigned capacity);
	int isFull(struct Queue* queue);
	int isEmpty(struct Queue* queue);
	void enqueue(struct Queue* queue, int item);
	int dequeue(struct Queue* queue);
	int front(struct Queue* queue);
	int rear(struct Queue* queue);