#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define DATA_SIZE 			2000000000		//8GB
#define MEM_SIZE 			25000000		//100MB
#define THREAD_NUM			4 //Try to get optimized #. Maybe CPU#
#define MEM_SIZE_SEGMENT	(int)(MEM_SIZE / THREAD_NUM)
#define K_THREAD 			(int)(DATA_SIZE / MEM_SIZE)
#define K					(K_THREAD * THREAD_NUM)
#define S 					(int)floor(MEM_SIZE / (K + 1))
#define OUTPUT 				(MEM_SIZE - S * K)
#define NUM_S_STILL_FIT 	(int)floor((MEM_SIZE - (K + 1) * S) / S)
#define LEFT_OVER 			(MEM_SIZE - (K + 1 + NUM_S_STILL_FIT) * S)
#define RAN_LOWER			0
#define RAN_UPPER			10

typedef int data_t;

data_t *M;

void *pThread_Load(void *Pa);
void *pThread_Sort(void *Pa);
void *pThread_Save(void *Pa);

int GenData();
void Load(int idx);
int Fill(int idx);
int FillLeftOver(int idx);
void Sort();
void Save(int idx);
void Store();
int LinearScan();
void KwayMerge();
int prin();
int check(int pri);

int isTmpLineEmptyHasLeftOver(int idx);
int isMemLineEmpty(int idx);
int isTmpLineEmpty(int idx);
int isTmpEmpty(int idx);

int *T_Fill_idx_list = NULL;
int *M_Lscan_idx_list = NULL;

struct pArg{ 
   int idx;
   int mem_offset;
};

pthread_mutex_t Load_lock;
pthread_mutex_t Save_lock;

int main(){
	remove("Data-3.dat");
	remove("Data-tmp-3.dat");
	remove("Data-sorted-3.dat");

	if (access("Data-3.dat", F_OK) != -1) {
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

	if (access("Data-sorted-3.dat", F_OK) != -1)
	    remove("Data-sorted-3.dat");

	M = (data_t *)malloc(MEM_SIZE * sizeof(data_t));
	T_Fill_idx_list = (int *)calloc(K, sizeof(int));
	M_Lscan_idx_list = (int *)calloc(K, sizeof(int));
	if (M == NULL || T_Fill_idx_list == NULL|| M_Lscan_idx_list == NULL){
		printf("Allocating failure. Exiting.\n");
		exit(EXIT_FAILURE);
	}

	if (pthread_mutex_init(&Load_lock, NULL) != 0 || pthread_mutex_init(&Save_lock, NULL) != 0){ 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 

	printf("Start sorting Phase...\n");
	pthread_t thread_id[THREAD_NUM];

	struct pArg Pa[THREAD_NUM];

	for (int i = 0; i < K_THREAD; i++){
		for (int j = 0; j < THREAD_NUM; j++){
			Pa[j].idx = THREAD_NUM * i + j;
			Pa[j].mem_offset = MEM_SIZE_SEGMENT * j;
		}

		for (int j = 0; j < THREAD_NUM; j++)
			pthread_create(&thread_id[j], NULL, pThread_Load, (void *)&Pa[j]);
		
		for (int j = 0; j < THREAD_NUM; j++){
			pthread_join(thread_id[j], NULL);
			pthread_create(&thread_id[j], NULL, pThread_Sort, (void *)&Pa[j]);
		}

		for (int j = 0; j < THREAD_NUM; j++){
			pthread_join(thread_id[j], NULL);
			pthread_create(&thread_id[j], NULL, pThread_Save, (void *)&Pa[j]);
		}

		for (int j = 0; j < THREAD_NUM; j++)
			pthread_join(thread_id[j], NULL);
	}

	pthread_mutex_destroy(&Load_lock);
	pthread_mutex_destroy(&Save_lock);

	for (int i = 0; i < K; i++){
		Fill(i);
	}

	printf("Start merging phase...\n");
	KwayMerge();

	free(M);
	remove("Data-tmp-3.dat");
	return 0;
}

void *pThread_Load(void *Pa)
{
	const char filename[] = "Data-3.dat";
    FILE *hs;
    int idx = ((struct pArg *)Pa)->idx;
    int mem_offset = ((struct pArg *)Pa)->mem_offset;

    pthread_mutex_lock(&Load_lock);

	hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        exit(EXIT_FAILURE);
    }
    fseek(hs, MEM_SIZE_SEGMENT * idx * 4, SEEK_SET);
	int res = fread(M + mem_offset, sizeof(int), MEM_SIZE_SEGMENT, hs);
	if (res != MEM_SIZE_SEGMENT){
		fputs("pThread_LOAD().Reading error",stderr);
		exit(EXIT_FAILURE);
	}
	fclose(hs);

	pthread_mutex_unlock(&Load_lock);

	pthread_exit(NULL);
}
void *pThread_Sort(void *Pa)
{
    int mem_offset = ((struct pArg *)Pa)->mem_offset;
	heapSort(M + mem_offset, MEM_SIZE_SEGMENT);

	pthread_exit(NULL);
}
void *pThread_Save(void *Pa)
{
	const char filename[] = "Data-tmp-3.dat";
    int a;
    FILE *hs;
    int mem_offset = ((struct pArg *)Pa)->mem_offset;

    pthread_mutex_lock(&Save_lock);

    hs = fopen(filename,"a");
    if( hs == NULL)
    {
        fprintf(stderr,"Error writing to %s\n",filename);
        exit(EXIT_FAILURE);
    }
	fwrite(M + mem_offset, sizeof(int), MEM_SIZE_SEGMENT, hs);
    fclose(hs);

    pthread_mutex_unlock(&Save_lock);

	pthread_exit(NULL);
}

void Load(int idx)
{
	const char filename[] = "Data-3.dat";
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

	const char filename[] = "Data-tmp-3.dat";
    FILE *hs;

	hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        exit(EXIT_FAILURE);
    }	

    fseek(hs, (idx * MEM_SIZE_SEGMENT + *(T_Fill_idx_list + idx) * S) * 4, SEEK_SET);
	int res = fread(M + idx * S, sizeof(int), S, hs);
	if (res != S){
		fputs("Fill().Reading error",stderr);
		exit(EXIT_FAILURE);
	}
	fclose(hs);

	(*(T_Fill_idx_list + idx))++;
	M_Lscan_idx_list[idx] = 0;
	return 0;
}
int FillLeftOver(int idx)
{
	const char filename[] = "Data-tmp-3.dat";
    FILE *hs;

	hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        exit(EXIT_FAILURE);
    }

	fseek(hs, (idx * MEM_SIZE_SEGMENT + *(T_Fill_idx_list + idx) * S) * 4, SEEK_SET);
    int res = fread(M + idx * S + S - LEFT_OVER, sizeof(int), LEFT_OVER, hs);
	if (res != LEFT_OVER){
		fputs("FillLeftOver().Reading error",stderr);
		exit(EXIT_FAILURE);
	}
	fclose(hs);

	(*(T_Fill_idx_list + idx))++;
	M_Lscan_idx_list[idx] = S - 1 - LEFT_OVER;
	return 0;
}


void Sort()
{
	heapSort(M, MEM_SIZE);
}

void Save(int idx)
{
	const char filename[] = "Data-tmp-3.dat";
    int a;
    FILE *hs;

    hs = fopen(filename,"a");
    if( hs == NULL)
    {
        fprintf(stderr,"Error writing to %s\n",filename);
        exit(EXIT_FAILURE);
    }
	fwrite(M, sizeof(int), MEM_SIZE, hs);
    fclose(hs);
}

int St_idx = 0;
void Store()
{
	const char filename[] = "Data-sorted-3.dat";
    int a;
    FILE *hs;

    hs = fopen(filename,"a");
    if( hs == NULL)
    {
        fprintf(stderr,"Error writing to %s\n",filename);
        exit(EXIT_FAILURE);
    }
	fwrite(M + MEM_SIZE - OUTPUT, sizeof(int), OUTPUT, hs);
    fclose(hs);

    St_idx++;
}

int LinearScan()
{
	int i = 0;
	while (isMemLineEmpty(i) && !isTmpEmpty(i))
		if(Fill(i))
			i++;
	int min = M[i * S + *(M_Lscan_idx_list + i)];
	int M_min_idx = i;
	i++;
	for (; i < K; i++){
		while (isMemLineEmpty(i) && !isTmpEmpty(i))
				if (Fill(i))
					i++;
		int LeftMost_idx = i * S + *(M_Lscan_idx_list + i);
		if (min > M[LeftMost_idx]){
			min = M[LeftMost_idx];
			M_min_idx = i;
		}			
	}
	(*(M_Lscan_idx_list + M_min_idx))++;
	return min;
}

void KwayMerge()
{
	
	int N = (int)floor(DATA_SIZE / OUTPUT);
	int n = N;
	int i = 0;
	int j = 1;
	int left_over = DATA_SIZE - N * OUTPUT;

	while (n-- > 0){
		for (int i = 0; i < OUTPUT; i++)
			M[MEM_SIZE - OUTPUT + i] = LinearScan();
		Store();
		if ((int)((i++ + 1) % (N / 10)) == 0)
			printf("%d%s\n", j++ * 10, "%");
	}
	for (int i = 0; i < left_over; i++)
		M[MEM_SIZE - OUTPUT + i] = LinearScan();
	Store();
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
	const char filename[] = "Data-3.dat";
    int a;
    FILE *hs;

    printf("Generating 8GB of random data...\n");
    hs = fopen(filename,"w");
    if( hs == NULL)
    {
        fprintf(stderr,"Error writing to %s\n",filename);
        return(1);
    }
	for (int l = 0; l < DATA_SIZE; l++){
			a = rand() % (RAN_UPPER - RAN_LOWER + 1) + RAN_LOWER;
		fwrite(&a, sizeof(int), 1, hs);
	}
    fclose(hs);
    
    return 0;
}

int prin()
{
	int D[RAN_UPPER - RAN_LOWER + 1];
	for (int j = 0; j < RAN_UPPER - RAN_LOWER + 1; j++)
		D[j] = 0;
	const char filename[] = "Data-3.dat";
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
        for (int j = 0; j < RAN_UPPER - RAN_LOWER + 1; j++)
        	if (a == j + RAN_LOWER){
    			D[j]++;
    			break;
    		}
    }
    for (int j = 0; j < RAN_UPPER - RAN_LOWER + 1; j++){
		printf("%d - %d\n", j, D[j]);
    }

    fclose(hs);
    return 0;
}

int check(int pri)
{
	int D[RAN_UPPER - RAN_LOWER + 1];
	for (int j = 0; j < RAN_UPPER - RAN_LOWER + 1; j++)
		D[j] = 0;
	const char filename[] = "Data-sorted-3.dat";
    int a;
    FILE *hs;
    hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        return(1);
    }

    if (pri == 1){
    	for (int i = 0; i < DATA_SIZE; i++){
        	fread(&a, sizeof(int), 1, hs);
        	printf("%d ",a);
        	for (int j = 0; j < RAN_UPPER - RAN_LOWER + 1; j++)
        		if (a == j + RAN_LOWER){
        			D[j]++;
        			break;
        		}
    	}
    }
    else{
    	for (int i = 0; i < DATA_SIZE; i++){
        	fread(&a, sizeof(int), 1, hs);
       	for (int j = 0; j < RAN_UPPER - RAN_LOWER + 1; j++)
        		if (a == j + RAN_LOWER){
        			D[j]++;
        			break;
        		}
    	}
    }
    
    printf("\n");
    for (int j = 0; j < RAN_UPPER - RAN_LOWER + 1; j++)
		printf("%d - %d\n", j, D[j]);

    fclose(hs);
    return 0;
}