#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include "MinHeap.h"
#include <unistd.h>
#include <math.h>
#include <time.h>

#define DATA_SIZE 			2000000000		//8GB
#define MEM_SIZE 			25000000		//100MB
// #define DATA_SIZE 			8000		//8GB
// #define MEM_SIZE 			100		//100MB
#define K 					(int)(DATA_SIZE / MEM_SIZE)
#define S 					(int)floor(MEM_SIZE / (K + 1))
#define OUTPUT 				(MEM_SIZE - S * K)
#define NUM_S_STILL_FIT 	(int)floor((MEM_SIZE - (K + 1) * S) / S)
#define LEFT_OVER 			(MEM_SIZE - (K + 1 + NUM_S_STILL_FIT) * S)
#define HEAP_SIZE			K
//#define MEM_SIZE_EXTRA (S * K - MEM_SIZE) //40

typedef int data_t;

//data_t *D; // Data (slow memory)
data_t *M; // Memory (fast memory)
//data_t *T; // Data tmp (slow memory)

int GenData();		//
void Load(int idx);	//
int Fill(int idx);	//
int FillLeftOver(int idx);
void Sort();		//
void Save(int idx);	//
void Store();		//
int LinearScan();
void KwayMerge();
int test();

int isTmpLineEmptyHasLeftOver(int idx);
int isMemLineEmpty(int idx);
int isTmpLineEmpty(int idx);
int isTmpEmpty(int idx);

int *T_Fill_idx_list = NULL;
int *M_Lscan_idx_list = NULL;
Heap *heap = NULL;


int main(){
	remove("Data.dat");
	remove("Data-tmp.dat");
	remove("Data-sorted.dat");

	// printf("%d\n", NUM_S_STILL_FIT);
	// printf("%d\n", LEFT_OVER);

	if (access("Data.dat", F_OK) != -1) {
	    printf("Data existed. Skip generating data.\n");
	} 
	else{
	    if (!GenData()){
			printf("Generating data successfully.\n");
		}
		else{
			printf("Generating data failed.\n");
			printf("Terminating program...\n");
			exit(EXIT_FAILURE);
		}
	}

	if (access("Data-sorted.dat", F_OK) != -1)
	    remove("Data-sorted.dat");
	
	heap = CreateHeap(HEAP_SIZE, 0);
	// D = (data_t *)malloc(DATA_SIZE * sizeof(data_t));
	M = (data_t *)malloc(MEM_SIZE * sizeof(data_t));
	//T = (data_t *)malloc(DATA_SIZE * sizeof(data_t));
	T_Fill_idx_list = (int *)calloc(K, sizeof(int));
	M_Lscan_idx_list = (int *)calloc(K, sizeof(int));

	if (M == NULL || T_Fill_idx_list == NULL|| M_Lscan_idx_list == NULL){
		printf("Allocating failure. Exiting.\n");
		exit(EXIT_FAILURE);
	}

	// srand(4);
	// for (int i = 0; i < DATA_SIZE; i++)
	// 	M[i] = rand() % (9 - 0 + 1) + 0;

	// for (int i = 0; i < K; i++){
	// 	for (int j = 0; j < MEM_SIZE; j++)
	// 		printf("%d ", D[i * MEM_SIZE + j]);
	// 	printf("\n");
	// }
	// printf("%s\n", "-----");
	printf("Start sorting Phase...\n");
	for (int i = 0; i < K; i++){
		//printf("Loading\n");
		Load(i);
		// printf("Sorting\n");
		Sort();
		// for (int j = 0; j < MEM_SIZE; j++)
		// 	printf("%d", M[j]);
		// printf("\n");
		// printf("Saving\n");
		Save(i);
		printf("%d/%d\n", i + 1, K);
	}

	// for (int i = 0; i < MEM_SIZE; i++)
	// 	M[i] = 1;

	// for (int i = 0; i < K; i++){
	// 	for (int j = 0; j < MEM_SIZE; j++)
	// 		printf("%d ", T[i * MEM_SIZE + j]);
	// 	printf("\n");
	// }
	 // printf("%s\n", "-----");

	for (int i = 0; i < K; i++){
		//printf("%d\n", i);
		Fill(i);
		// for (int j = 0; j < MEM_SIZE; j++)
		// 	printf("%d", M[j]);
		// printf("\n");
	}


	// printf("After 1st fill\n");
	// for (int i = 0; i < K + 1; i++){
	// 	for (int j = 0; j < S; j++)
	// 		printf("%d", M[i * S + j]);
	// 	printf("\n");
	// }
	// printf("%s\n", "-----");

	// for (int i = 0; i < S; i++)
	// 		M[MEM_SIZE - S + i] = LinearScan();
	// Store();

	// for (int j = 0; j < MEM_SIZE; j++)
	// 	printf("%d ", M[j]);
	// printf("%s\n", "-----");
	printf("Start merging phase...\n");
	for (int i = 0; i < K; i++)
		insert(heap, M[i * S]);
	printf(" %d ", heap->count);
	KwayMerge();

	// for (int i = 0; i < K; i++){
	// 	for (int j = 0; j < MEM_SIZE; j++)
	// 		printf("%d ", D[i * MEM_SIZE + j]);
	// 	printf("\n");
	// }

	// free(D);
	free(M);
	//free(T);
	remove("Data-tmp.dat");
	//test();
	return 0;
}

void Load(int idx)
{
	// for(int i = 0; i < MEM_SIZE; i++)
	// 	M[i] = D[MEM_SIZE * idx + i];

	const char filename[] = "Data.dat";
    FILE *hs;

	hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        exit(EXIT_FAILURE);
    }

    fseek(hs, MEM_SIZE * idx * 4, SEEK_SET);
	int res = fread(M, sizeof(int), MEM_SIZE, hs);
	if (res != MEM_SIZE){
		fputs("LOAD().Reading error",stderr);
		exit(EXIT_FAILURE);
	}
	fclose(hs);
}

int Fill(int idx)
{
	if (isTmpLineEmpty(idx)){
		if (isTmpLineEmptyHasLeftOver(idx)){
			FillLeftOver(idx);
			return 0;
		}
		return 1;
	}
	// if (isTmpEmpty(idx))
	// 	return 1;
	
	const char filename[] = "Data-tmp.dat";
    FILE *hs;

	hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        exit(EXIT_FAILURE);
    }

    fseek(hs, (idx * MEM_SIZE + *(T_Fill_idx_list + idx) * S) * 4, SEEK_SET);
    // for (int i = 0; i < K; i++)
    // 	printf("%d", *(T_Fill_idx_list + i));
    // printf("\n");
    //printf("-%d %d %d %d\n", idx, idx * MEM_SIZE, *(T_Fill_idx_list + idx), idx * MEM_SIZE + *(T_Fill_idx_list + idx) * S);
	int res = fread(M + idx * S, sizeof(int), S, hs);
	//printf("%d\n", res);
	if (res != S){
		fputs("Fill().Reading error",stderr);
		exit(EXIT_FAILURE);
	}
	(*(T_Fill_idx_list + idx))++;
	M_Lscan_idx_list[idx] = 0;
	fclose(hs);
	return 0;
}
int FillLeftOver(int idx)
{
	const char filename[] = "Data-tmp.dat";
    FILE *hs;

	hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        exit(EXIT_FAILURE);
    }
    //printf("-> M[%d] %d\n", S*idx, idx * MEM_SIZE + *(T_Fill_idx_list + idx) * S);
    fseek(hs, (idx * MEM_SIZE + *(T_Fill_idx_list + idx) * S) * 4, SEEK_SET);
    
    int res = fread(M + idx * S, sizeof(int), 1, hs);
	if (res != 1){
		fputs("FillLeftOver().Reading error",stderr);
		exit(EXIT_FAILURE);
	}
	(*(T_Fill_idx_list + idx))++;
	M_Lscan_idx_list[idx] = S - 1 - LEFT_OVER;
	fclose(hs);
	return 0;
}


void Sort()
{
	heapSort(M, MEM_SIZE);
}

void Save(int idx)
{
	// for(int i = 0; i < MEM_SIZE; i++)
	// 	T[MEM_SIZE * idx + i] = M[i];

	const char filename[] = "Data-tmp.dat";
    int a;
    FILE *hs;

    //printf("Generating 8GB random data...\n");
    hs = fopen(filename,"a");
    if( hs == NULL)
    {
        fprintf(stderr,"Error writing to %s\n",filename);
        exit(EXIT_FAILURE);
    }
    
    // int *a = (int *)malloc() // => check if this way is faster

    // for (int i = 0; i < 9; i++) //GB
   	// 	for (int j = 0; j < 1000; j++) //MB
   	// 		for (int k = 0; k < 1000; k++) //KB
   	// 			for (int l = 0; l < 250; l++){ //4B
    			// for (int l = 0; l < DATA_SIZE; l++){
   					//a = rand() % (9 - 0 + 1) + 0;
        			fwrite(M, sizeof(int), MEM_SIZE, hs);
   				//}
    fclose(hs);
}

int St_idx = 0;
void Store()
{
	// for (int i = 0; i < S; i++)
	// 	D[St_idx * S + i] = M[MEM_SIZE - S + i];
	//St_idx++;

	const char filename[] = "Data-sorted.dat";
    int a;
    FILE *hs;

    hs = fopen(filename,"a");
    if( hs == NULL)
    {
        fprintf(stderr,"Error writing to %s\n",filename);
        exit(EXIT_FAILURE);
    }
    //fseek(hs, (St_idx * S) * 4, SEEK_SET);
	fwrite(M + MEM_SIZE - OUTPUT, sizeof(int), OUTPUT, hs);
    fclose(hs);
    St_idx++;
}

int LinearScan()
{
// {
// 	int i = 0;
// 	while (isMemLineEmpty(i) && !isTmpEmpty(i))
// 		if(Fill(i))
// 			i++;
// 	int min = M[i * S + *(M_Lscan_idx_list + i)];
// 	int M_min_idx = i;
// 	i++;
// 	for (; i < K; i++){
// 		while (isMemLineEmpty(i) && !isTmpEmpty(i))
// 				if (Fill(i))
// 					i++;
// 		int LeftMost_idx = i * S + *(M_Lscan_idx_list + i);
// 		if (min > M[LeftMost_idx]){
// 			min = M[LeftMost_idx];
// 			M_min_idx = i;
// 		}			
// 	}
// 	(*(M_Lscan_idx_list + M_min_idx))++;

	// for (int i = 0; i < K; i++){
	// 	while (isMemLineEmpty(i) && !isTmpEmpty(i))
	// 			if (Fill(i))
	// 				i++;
	// 	int LeftMost_idx = i * S + *(M_Lscan_idx_list + i);
	// 	insert(heap, M[LeftMost_idx])
	// }
	int min = PopMin(heap);
	printf(" %d ", heap->count);
	int M_min_idx;
	int idx;
	for (int i = 0; i < K; i++){
		int LeftMost_idx = i * S + *(M_Lscan_idx_list + i);
		if (!isMemLineEmpty(i))
			if (min = M[LeftMost_idx]){
				M_min_idx = i;
				(*(M_Lscan_idx_list + M_min_idx))++;
				break;
			}
	}

	if (!isMemLineEmpty(M_min_idx)){
		insert(heap, M[M_min_idx * S + *(M_Lscan_idx_list + M_min_idx)]);
		return min;
	}

	if (isMemLineEmpty(M_min_idx))
		if (!isTmpEmpty(M_min_idx))
			if (!Fill(M_min_idx))
				insert(heap, M[M_min_idx * S + *(M_Lscan_idx_list + M_min_idx)]);

	return min;
}

void KwayMerge()
{
	int N = (int)DATA_SIZE / OUTPUT;
	int n = N;
	int i = 0;
	int j = 1;
	while (n-- > 0){
		for (int i = 0; i < OUTPUT; i++)
			M[MEM_SIZE - OUTPUT + i] = LinearScan();
		// printf("\n");
		// for (int i = 0; i < K + 1; i++){
		// 	for (int j = 0; j < S; j++)
		// 		printf("%d ", M[i * S + j]);
		// }
		// for (int j = 0; j < MEM_SIZE; j++)
		// 	printf("%d ", M[j]);
		// printf("\n");
		Store();
		if ((int)((i++ + 1) % (N / 10)) == 0)
			printf("%d%s\n", j++ * 10, "%");
	}
}

int isMemLineEmpty(int idx)
{
	if (*(M_Lscan_idx_list + idx) >= S)
		return 1;
	else
		return 0;
}

int isTmpLineEmptyHasLeftOver(int idx)
{
	if (*(T_Fill_idx_list + idx) == K + 1 + NUM_S_STILL_FIT + 1)
		return 0;
	else
		return 1;
}

int isTmpLineEmpty(int idx)
{
	if (*(T_Fill_idx_list + idx) >= K + 1 + NUM_S_STILL_FIT){
		return 1;
	}
	else
		return 0;
}

int isTmpEmpty(int idx){
	if (idx == K)
		return 1;
	else
		return 0;
}

int GenData()
{
	const char filename[] = "Data.dat";
    int a;
    FILE *hs;

    printf("Generating 8GB of random data...\n");
    hs = fopen(filename,"w");
    if( hs == NULL)
    {
        fprintf(stderr,"Error writing to %s\n",filename);
        return(1);
    }
    
    // int *a = (int *)malloc() // => check if this way is faster

    // for (int i = 0; i < 9; i++) //GB
   	// 	for (int j = 0; j < 1000; j++) //MB
   	// 		for (int k = 0; k < 1000; k++) //KB
   	// 			for (int l = 0; l < 250; l++){ //4B
    			for (int l = 0; l < DATA_SIZE; l++){
   					a = rand() % (9 - 1 + 1) + 1;
        			fwrite(&a, sizeof(int), 1, hs);
   				}
    fclose(hs);
    // hs = fopen(filename,"r");
    // if( hs == NULL)
    // {
    //     fprintf(stderr,"Error reading from  %s\n",filename);
    //     return(1);
    // }

    // for (int i = 0; i < 10; i++){
    //     fread(&score, sizeof(int), 1, hs);
    //     printf("Reading high score: %d\n",score);
    // }
    // fclose(hs);
    return 0;
}

int test(){
	const char filename[] = "Data-sorted.dat";
    int a;
    FILE *hs;
    hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        return(1);
    }

    for (int i = 0; i < DATA_SIZE; i++){
        fread(&a, sizeof(int), 1, hs);
        printf("%d",a);
    }

    fclose(hs);
    return 0;
}