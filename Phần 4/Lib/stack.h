#define STACK_TYPE 2 // array: 1 - linkedlist: 2

#if STACK_TYPE == 1

	#define __STACK_ARRAY_BASE__
	struct Stack 
	{ 
	    int top; 
	    unsigned capacity; 
	    int* array; 
	};
	struct Stack* createStack(unsigned capacity);
	int isFull_s(struct Stack* stack);
	int isEmpty_s(struct Stack* stack);
	void push_s(struct Stack* stack, int item);
	int pop_s(struct Stack* stack);
	
#endif

#if STACK_TYPE == 2

	#define __STACK_LINKED_LIST_BASE__
	struct Stack 
	{
		int size;
	    unsigned capacity; 
	    struct Node *head; 
	};
	struct Stack* createStack(unsigned capacity);
	int isFull_s(struct Stack* stack);
	int isEmpty_s(struct Stack* stack);
	void push_s(struct Stack* stack, int item);
	int pop_s(struct Stack* stack);

#endif

	