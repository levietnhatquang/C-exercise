#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

////////////////////////////////SINGLE LINKED LIST
#ifdef __SINGLE_LINKED_LIST__
//insert at head
void Push(struct Node **head_ref, int new_data)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = *head_ref;
	*head_ref = new_node;
}
//insert random
void Insertafter(struct Node *prev_node, int new_data)
{
	if (prev_node == NULL){
		return;
	}
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
}
//insert at last
void Append(struct Node **head_ref, int new_data)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	struct Node *last = *head_ref;
	new_node->data = new_data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return;
}

void Deletenode(struct Node **head_ref, int key)
{
	struct Node *tmp = *head_ref, *prev;
	if (tmp != NULL && tmp->data == key)
	{
		*head_ref = tmp->next;
		free(tmp);
		return;
	}
	while (tmp != NULL && tmp->data != key)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return;
	prev->next = tmp->next;
	free(tmp);
}

void Printlist(struct Node *node)
{
	while (node != NULL){
		printf(" %d ", node->data);
		node = node->next;
	}
}
#endif

////////////////////////////////DOUBLE LINKED LIST
#ifdef __DOUBLE_LINKED_LIST__
//insert at head
void Push(struct Node **head_ref, int new_data)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = *head_ref;
	new_node->prev = NULL;
	if(*head_ref != NULL)
		(*head_ref)->prev = new_node;
	*head_ref = new_node;
}
//insert random
void Insertafter(struct Node *prev_node, int new_data)
{
	if (prev_node == NULL){
		return;
	}
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if(prev_node->next != NULL)
		prev_node->next->prev = new_node;
	prev_node->next = new_node;
}
//insert at last
void Append(struct Node **head_ref, int new_data)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	struct Node *last = *head_ref;
	new_node->data = new_data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return;
}

void Deletenode(struct Node **head_ref, int key)
{
	struct Node *tmp = *head_ref, *prev;
	if (tmp != NULL && tmp->data == key)
	{
		tmp->next->prev = tmp->prev;
		*head_ref = tmp->next;
		free(tmp);
		return;
	}
	while (tmp != NULL && tmp->data != key)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return;
	prev->next = tmp->next;
	tmp->next->prev = prev;
	free(tmp);
}

void Printlist(struct Node *node)
{
	while (node != NULL){
		printf(" %d ", node->data);
		node = node->next;
	}
}
#endif

/////////////////////////////////CIRCLE LINKED LIST
#ifdef __CIRCLE_LINKED_LIST__
//insert at head
void Push(struct Node **head_ref, int new_data)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node)), *tmp;
	tmp = *head_ref;
	new_node->data = new_data;
	if(*head_ref == NULL)
		new_node->next = new_node;
	else{
		new_node->next = *head_ref;
		while(tmp->next != *head_ref)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	*head_ref = new_node;
}
//insert random
void Insertafter(struct Node *prev_node, int new_data)
{
	if (prev_node == NULL){
		return;
	}
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
}
//insert at last
void Append(struct Node **head_ref, int new_data)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	struct Node *last = *head_ref;
	new_node->data = new_data;
	new_node->next = *head_ref;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		new_node->next = new_node;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return;
}

void Deletenode(struct Node **head_ref, int key)
{
	struct Node *tmp = *head_ref, *prev;
	if (tmp != NULL && tmp->data == key)
	{
		*head_ref = tmp->next;
		free(tmp);
		return;
	}
	while ((tmp = tmp->next) != *head_ref && tmp->data != key)
		prev = tmp;
	prev->next = tmp->next;
	free(tmp);
}

void Printlist(struct Node *head_ref)
{
	struct Node *tmp = head_ref;
	do{
		printf(" %d ", tmp->data);
	}while ((tmp = tmp->next) != head_ref);
}
#endif