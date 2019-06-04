#ifndef LINKED_LIST_TYPE
	#define LINKED_LIST_TYPE 1 // singly: 1 - doubly: 2 - circly: 3
#endif

#if QUEUE_TYPE == 2 || STACK_TYPE == 2
	#undef LINKED_LIST_TYPE
	#define LINKED_LIST_TYPE 1
#endif

#if LINKED_LIST_TYPE == 1
	#define __SINGLE_LINKED_LIST__
	struct Node
	{
		int data;
		struct Node *next;
	};

	void Push(struct Node **head_ref, int new_data);
	void Insertafter(struct Node *prev_node, int new_data);
	void Append(struct Node **head_ref, int new_data);
	void Deletenode(struct Node **head_ref, int key);
	void Printlist(struct Node *node);
#endif

#if LINKED_LIST_TYPE == 2
	#define __DOUBLE_LINKED_LIST__
	struct Node
	{
		int data;
		struct Node *next;
		struct Node *prev;
	};

	void Push(struct Node **head_ref, int new_data);
	void Insertafter(struct Node *prev_node, int new_data);
	void Append(struct Node **head_ref, int new_data);
	void Deletenode(struct Node **head_ref, int key);
	void Printlist(struct Node *node);
#endif

#if LINKED_LIST_TYPE == 3
	#define __CIRCLE_LINKED_LIST__
	struct Node
	{
		int data;
		struct Node *next;
	};

	void Push(struct Node **head_ref, int new_data);
	void Insertafter(struct Node *prev_node, int new_data);
	void Append(struct Node **head_ref, int new_data);
	void Deletenode(struct Node **head_ref, int key);
	void Printlist(struct Node *head_ref);
#endif

