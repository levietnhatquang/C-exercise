#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include <unistd.h>
#include <math.h>
#include <time.h>

#define DATA_SIZE 			2000000000		//8GB
#define MEM_SIZE 			25000000		//100MB
#define K 					(int)(DATA_SIZE / MEM_SIZE)
#define S 					(int)floor(MEM_SIZE / (K + 1))
#define OUTPUT 				(MEM_SIZE - S * K)
#define NUM_S_STILL_FIT 	(int)floor((MEM_SIZE - (K + 1) * S) / S)
#define LEFT_OVER 			(MEM_SIZE - (K + 1 + NUM_S_STILL_FIT) * S)

typedef int data_t;

data_t *M;

int GenData();
void Load(int idx);
int Fill(int idx);
int FillLeftOver(int idx);
void Sort();
void Save(int idx);
void Store();
int LinearScan();
void KwayMerge();
int test();

int isTmpLineEmptyHasLeftOver(int idx);
int isMemLineEmpty(int idx);
int isTmpLineEmpty(int idx);
int isTmpEmpty(int idx);

int *T_Fill_idx_list = NULL;
int *M_Lscan_idx_list = NULL;


int main(){
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

	M = (data_t *)malloc(MEM_SIZE * sizeof(data_t));
	T_Fill_idx_list = (int *)calloc(K, sizeof(int));
	M_Lscan_idx_list = (int *)calloc(K, sizeof(int));

	if (M == NULL || T_Fill_idx_list == NULL|| M_Lscan_idx_list == NULL){
		printf("Allocating failure. Exiting.\n");
		exit(EXIT_FAILURE);
	}

	printf("Start sorting Phase...\n");
	for (int i = 0; i < K; i++){
		Load(i);
		Sort();
		Save(i);
		printf("%d/%d\n", i + 1, K);
	}

	for (int i = 0; i < K; i++){
		Fill(i);
	}

	printf("Start merging phase...\n");
	KwayMerge();

	free(M);
	remove("Data-tmp.dat");
	return 0;
}

void Load(int idx)
{
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

	const char filename[] = "Data-tmp.dat";
    FILE *hs;

	hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        exit(EXIT_FAILURE);
    }

    fseek(hs, (idx * MEM_SIZE + *(T_Fill_idx_list + idx) * S) * 4, SEEK_SET);
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
	const char filename[] = "Data-tmp.dat";
    FILE *hs;

	hs = fopen(filename,"r");
    if( hs == NULL)
    {
        fprintf(stderr,"Error reading from  %s\n",filename);
        exit(EXIT_FAILURE);
    }

	fseek(hs, (idx * MEM_SIZE + *(T_Fill_idx_list + idx) * S) * 4, SEEK_SET);
    int res = fread(M + idx * S, sizeof(int), 1, hs);
	if (res != 1){
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
	const char filename[] = "Data-tmp.dat";
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
	const char filename[] = "Data-sorted.dat";
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
	int N = (int)DATA_SIZE / OUTPUT;
	int n = N;
	int i = 0;
	int j = 1;
	while (n-- > 0){
		for (int i = 0; i < OUTPUT; i++)
			M[MEM_SIZE - OUTPUT + i] = LinearScan();
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
	for (int l = 0; l < DATA_SIZE; l++){
			a = rand() % (9 - 1 + 1) + 1;
		fwrite(&a, sizeof(int), 1, hs);
		}
    fclose(hs);
    
    return 0;
}
