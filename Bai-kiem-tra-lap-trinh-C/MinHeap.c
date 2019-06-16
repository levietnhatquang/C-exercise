#include<stdio.h>
#include<stdlib.h>
/*
 Array Implementation of MinHeap data Structure
*/

int HEAP_SIZE = 20;

struct Heap{
    int *arr;
    int count;
    int capacity;
    int heap_type; // 0 for min heap , 1 for max heap
};
typedef struct Heap Heap;

Heap *CreateHeap(int capacity,int heap_type);
void insert(Heap *h, int key);
void print(Heap *h);
void heapify_bottom_top(Heap *h,int index);
void heapify_top_bottom(Heap *h, int parent_node);
int PopMin(Heap *h);

int main(){
    int i;
    Heap *heap = CreateHeap(HEAP_SIZE, 0); //Min Heap
    if (heap == NULL){
        printf("CreateHeap() failed.\n");
        return -1;
    }

    for (i = 9; i > 0; i--)
        insert(heap, i);

    print(heap);

    for (i = 9; i >= 0; i--){
        printf(" Pop Minima : %d\n", PopMin(heap));
        print(heap);
    }
    return 0;
}

Heap *CreateHeap(int capacity,int heap_type){
    Heap *h = (Heap * ) malloc(sizeof(Heap)); //one is number of heap

    //check if memory allocation is fails
    if(h == NULL){
        printf("Memory Error!");
        exit(EXIT_FAILURE);
    }
    h->heap_type = heap_type;
    h->count=0;
    h->capacity = capacity;
    h->arr = (int *) malloc(capacity*sizeof(int)); //size in bytes

    //check if allocation succeed
    if ( h->arr == NULL){
        printf("Memory Error!");
        exit(EXIT_FAILURE);
    }
    return h;
}

void insert(Heap *h, int key){
    if( h->count < h->capacity){
        h->arr[h->count] = key;
        heapify_bottom_top(h, h->count);
        h->count++;
    }
}

void heapify_bottom_top(Heap *h,int index){
    int temp;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node] > h->arr[index]){
        //swap and recursive call
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->arr[index] = temp;
        heapify_bottom_top(h,parent_node);
    }
}

void heapify_top_bottom(Heap *h, int parent_node){
    int left = parent_node*2+1;
    int right = parent_node*2+2;
    int min;
    int temp;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;

    if(left != -1 && h->arr[left] < h->arr[parent_node])
        min=left;
    else
        min =parent_node;
    if(right != -1 && h->arr[right] < h->arr[min])
        min = right;

    if(min != parent_node){
        temp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = temp;

        // recursive  call
        heapify_top_bottom(h, min);
    }
}

int PopMin(Heap *h){
    int pop;
    if(h->count==0){
        printf("\n__Heap is Empty__\n");
        return -1;
    }
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}
void print(Heap *h){
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        printf("-> %d ",h->arr[i]);
    }
    printf("->__/\\__\n");
}


// https://robin-thomas.github.io/min-heap/
// #define LCHILD(x) (2 * x + 1)
// #define RCHILD(x) (2 * x + 2)
// #define PARENT(x) ((x - 1) / 2)

// typedef struct node{
//     int data;
// }node;

// typedef struct minHeap{
//     int size;
//     node *elem;
// }minHeap;

// minHeap initMinHeap(int size){
//     minHeap hp;
//     hp.size = 0;
//     return hp;
// }

// void swap(node *n1, node *n2) {
//     node temp = *n1;
//     *n1 = *n2;
//     *n2 = temp;
// }

// void insertNode(minHeap *hp, int data)
// {
//     // allocating space
//     if (hp->size)
//         hp->elem = realloc(hp->elem, (size + 1) * sizeof(node));
//     else
//         hp->elem = malloc(sizeof(node));

//     // initializing the node with value
//     node nd;
//     nd.data = data;

//     // Positioning the node at the right position in the min heap
//     int i = (hp->size)++;
//     while(i && nd.data < hp->elem[PARENT(i)].data){
//         hp->elem[i] = hp->elem[PARENT(i)];
//         i = PARENT(i);
//     }
//     hp->elem[i] = nd;
// }

// void heapify(minHeap *hp, int i){
//     int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].data < hp->elem[i].data) ? LCHILD(i) : i;
//     if (RCHILD(i) < hp->size && hp->elem[RCHILD(i)].data < hp->elem[largest].data){
//         smallest = RCHILD(i);
//     }
//     if (smallest != i) {
//         swap(&(hp->elem[i]), &(hp->elem[smallest])) 
//         heapify(hp, smallest);
//     }
// }

// void deleteNode(minHeap *hp) {
//     if(hp->size){
//         printf("Deleting node %d\n\n", hp->elem[0].data);
//         hp->elem[0] = hp->elem[--(hp->size)];
//         hp->elem = realloc(hp->elem, hp->size * sizeof(node));
//         heapify(hp, 0);
//     }
//     else{
//         printf("\nMin Heap is empty!\n");
//         free(hp->elem);
//     }
// }

// void buildMinHeap(minHeap *hp, int *arr, int size) {
//     int i;

//     // Insertion into the heap without violating the shape property
//     for (i = 0; i < size; i++){
//         if (hp->size)
//             hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node));
//         else
//             hp->elem = malloc(sizeof(node));
//         node nd ;
//         nd.data = arr[i] ;
//         hp->elem[(hp->size)++] = nd;
//     }
//     // Making sure that heap property is also satisfied
//     for (i = (hp->size - 1) / 2; i >= 0; i--) {
//         heapify(hp, i);
//     }
// }


// int main(){
//     minHeap hp = initMinHeap();
//     return 0;
// }