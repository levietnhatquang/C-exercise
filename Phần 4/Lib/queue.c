#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include "queue.h"
#include "linkedList.h"

#ifdef __QUEUE_ARRAY_BASE__
struct Queue* createQueue(unsigned capacity) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;
    queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
    return queue; 
} 
  
int isFull(struct Queue* queue) 
{  return (queue->size == queue->capacity);  } 
  
int isEmpty(struct Queue* queue) 
{  return (queue->size == 0); } 
  
void enqueue(struct Queue* queue, int item) 
{ 
    if (isFull(queue)) 
        return; 
    queue->rear = (queue->rear + 1)%queue->capacity; 
    queue->array[queue->rear] = item; 
    queue->size = queue->size + 1; 
    printf("%d enqueued to queue\n", item); 
} 
  
int dequeue(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    int item = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
} 
  
int front(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->front]; 
} 
  
int rear(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->rear]; 
}
#endif

#ifdef __QUEUE_LINKED_LIST_BASE__
  
struct Queue* createQueue(unsigned capacity) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->head = (struct Node *) malloc(sizeof(struct Node));
    queue->size = 0;
    queue->capacity = capacity;
    return queue; 
} 
  
int isFull(struct Queue* queue) 
{  return (queue->size == queue->capacity);  } 
  
int isEmpty(struct Queue* queue) 
{  return (queue->size == 0); } 
  
void enqueue(struct Queue* queue, int item) 
{ 
    if (isFull(queue)) 
        return; 
    Push(&(queue->head), item);
    queue->size = queue->size + 1; 
    printf("%d enqueued to queue\n", item); 
} 
  
int dequeue(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    struct Node *tmp = queue->head, *prev_node;
    while (tmp->next != NULL){
        prev_node = tmp;
        //printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
    prev_node->next = NULL;
    int item = prev_node->data;
    free(tmp);
    queue->size = queue->size - 1;
    return item; 
} 
  
int front(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    struct Node *tmp = queue->head;
    while (tmp != NULL)
        tmp = tmp->next; 
    int item = tmp->data;
    return item; 
} 
  
int rear(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->head->data; 
}
#endif