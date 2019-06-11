#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

#define DATA_SIZE 1800
#define MEM_SIZE 200
#define K (int)(DATA_SIZE / MEM_SIZE)
#define S (int)(MEM_SIZE / (K + 1))

typedef int data_t;

data_t *D; // Data (slow memory)
data_t *M; // Memory (fast memory)
data_t *T; // Data tmp (slow memory)

void Load(int idx);
int Fill(int idx);
void Sort();
void Save(int idx);
void Store();
int LinearScan();
void KwayMerge();

int isMemLineEmpty(int idx);
int isTmpLineEmpty(int idx);

int *T_Fill_idx_list = NULL;
int *M_Lscan_idx_list = NULL;


int main(){
	D = (data_t *)malloc(DATA_SIZE * sizeof(data_t));
	M = (data_t *)malloc(MEM_SIZE * sizeof(data_t));
	T = (data_t *)malloc(DATA_SIZE * sizeof(data_t));
	T_Fill_idx_list = (int *)calloc(K, sizeof(int));
	M_Lscan_idx_list = (int *)calloc(K, sizeof(int));

	srand(4);
	for (int i = 0; i < DATA_SIZE; i++)
		D[i] = rand() % (9 - 0 + 1) + 0;

	for (int i = 0; i < K; i++){
		for (int j = 0; j < MEM_SIZE; j++)
			printf("%d ", D[i * MEM_SIZE + j]);
		printf("\n");
	}
	printf("%s\n", "-----");

	for (int i = 0; i < K; i++){
		Load(i);
		Sort();
		Save(i);
	}

	// for (int i = 0; i < MEM_SIZE; i++)
	// 	M[i] = 1;

	// for (int i = 0; i < K; i++){
	// 	for (int j = 0; j < MEM_SIZE; j++)
	// 		printf("%d ", T[i * MEM_SIZE + j]);
	// 	printf("\n");
	// }
	// printf("%s\n", "-----");

	for (int i = 0; i < K; i++)
		Fill(i);

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

	KwayMerge();

	for (int i = 0; i < K; i++){
		for (int j = 0; j < MEM_SIZE; j++)
			printf("%d ", D[i * MEM_SIZE + j]);
		printf("\n");
	}

	free(D);
	free(M);
	free(T);
	return 0;
}

void Load(int idx)
{
	for(int i = 0; i < MEM_SIZE; i++)
		M[i] = D[MEM_SIZE * idx + i];
}

int Fill(int idx)
{
	if (isTmpLineEmpty(idx))
		return 1;
	for (int i = 0; i < S; i++)
		M[idx * S + i] = T[idx * MEM_SIZE + *(T_Fill_idx_list + idx) * S + i];
	(*(T_Fill_idx_list + idx))++;
	M_Lscan_idx_list[idx] = 0;
	return 0;
}

void Sort()
{
	quickSort(M, 0, MEM_SIZE-1);
}

void Save(int idx)
{
	for(int i = 0; i < MEM_SIZE; i++)
		T[MEM_SIZE * idx + i] = M[i];
}

int St_idx = 0;
void Store()
{
	for (int i = 0; i < S; i++)
		D[St_idx * S + i] = M[MEM_SIZE - S + i];
	St_idx++;
}

int LinearScan()
{
	int i = 0;
	// for (int j = 0; j < K; j++)
	// 	printf("%d", *(M_Lscan_idx_list + j));
	// printf("\n");
	while (isMemLineEmpty(i))
		if(Fill(i))
			i++;
	int min = M[i * S + *(M_Lscan_idx_list + i)];
	int M_min_idx = i;
	i++;
	for (; i < K; i++){
		while (isMemLineEmpty(i))
			if(Fill(i))
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
	int n = (int)DATA_SIZE / S;
	while (n-- > 0){
		for (int i = 0; i < S; i++)
			M[MEM_SIZE - S + i] = LinearScan();
		//printf("\n");
		// for (int i = 0; i < K + 1; i++){
		// 	for (int j = 0; j < S; j++)
		// 		printf("%d ", M[i * S + j]);
		// }
		// for (int j = 0; j < MEM_SIZE; j++)
		// 	printf("%d ", M[j]);
		// printf("\n");
		Store();
	}
}

int isMemLineEmpty(int idx)
{
	if (*(M_Lscan_idx_list + idx) == S)
		return 1;
	else
		return 0;
}

int isTmpLineEmpty(int idx)
{
	if (*(T_Fill_idx_list + idx) == K + 1){
		// printf("Temp Line Empty\n");
		return 1;
	}
	else
		return 0;
}