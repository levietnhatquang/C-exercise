/*
 * Test the random-number generator on your system by generating N
 * random integers between 0 and r 1 with rand() % r and computing the
 * average and standard deviation for r = 10, 100, and 1000 and N 103 , 10\
 * 105 , and 106 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000
#define R 10

int sum(int arr[]);
float average(int arr[]);
float standard_deviation(int arr[]);
int A[N];

int main(){
	for (int i = 0; i < N; i++)
		A[i] = rand() % R;
	printf("Average: %f\n", average(A));
	printf("Standard deviation: %f\n", standard_deviation(A));
	return 0;
}

int sum(int arr[]) 
{ 
    int sum = 0;  
    for (int i = 0; i < N; i++) 
    	sum += arr[i]; 
    return sum; 
}

float average(int arr[])
{
	return (float)sum(arr) / N;
}

float standard_deviation(int arr[])
{
	float m = average(arr);
	int t = 0;
	for (int i = 0; i < N; i++){
		t += (float)pow((double)(arr[i] - m), 2);
	}
	return (float)sqrt(t / N);
}
