#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "queue.h"
#include "stack.h"

void main(){
	struct Node *head = NULL; 
  
    Push(&head, 7); 
    Push(&head, 1); 
    Push(&head, 3); 
    Push(&head, 2); 
  
    puts("Created Linked List: "); 
    Printlist(head); 
    Deletenode(&head, 1); 
    puts("\nLinked List after Deletion of 1: "); 
    Printlist(head); 

    puts("\n");
    struct Queue* queue = createQueue(1000); 
  
    enqueue(queue, 10); 
    enqueue(queue, 20); 
    enqueue(queue, 30); 
    enqueue(queue, 40); 
  
    printf("%d dequeued from queue\n\n", dequeue(queue));
  
    // printf("Front item is %d\n", front(queue)); 
    printf("Rear item is %d\n", rear(queue));

    struct Stack* stack = createStack(100); 
  
    push_s(stack, 10); 
    push_s(stack, 20); 
    push_s(stack, 30); 
  
    printf("%d popped from stack\n", pop_s(stack));

    
}