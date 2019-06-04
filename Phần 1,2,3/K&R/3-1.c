/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside). Write a version with only one
 * test inside the loop and measure the difference in run-time.
 */
#include<stdio.h>
#define MAXTEST 1000000
#include<time.h>

int binsearch_v1(int x, int v[], int n);
int binsearch_v2(int x, int v[], int n);

int main(){
	int c[MAXTEST];
	for(int i = 0; i < MAXTEST; i++){
		*(c + i) = i;
	}
	clock_t v1_start = clock();
	binsearch_v1(2500, c, MAXTEST);
	clock_t v1_stopt = clock();

	clock_t v2_start = clock();
	binsearch_v2(2500, c, MAXTEST);
	clock_t v2_stopt = clock();

	double v1_duration = (double)(v1_stopt - v1_start) / CLOCKS_PER_SEC;
	double v2_duration = (double)(v2_stopt - v2_start) / CLOCKS_PER_SEC;

	printf("V1 takes: %f s\n", v1_duration);
	printf("V2 takes: %f s\n", v2_duration);
	return 0;
}

int binsearch_v1(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else 
			return mid;
	}
	return -1;
}
int binsearch_v2(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	} 
	if ( x == v[mid] )
        return mid;
    else
        return -1;
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 3-1.c -o 3-1
 * quanglvn@quanglvn:~/thuviec/123$ ./3-1
 * V1 takes: 0.000002 s
 * V2 takes: 0.000001 s
 */