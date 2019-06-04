#include <stdio.h>
#include <stdlib.h>

#define N1 1000
#define N2 10000
#define N3 100000
#define N4 1000000

void sieve_int(long n, int *arr);

void main(){ 	 
	long i, cnt = 0;

	int *arr = (int *) malloc(N4*sizeof(int));
	if (arr == NULL) {
	printf("Allocation failed\n");
	return ;
	}

	sieve_int(N4, arr);

	for (i = 0; i < N1; ++i)
		if (arr[i])
			++cnt;
	printf("#primes <= 1000: %ld\n", cnt);

	for (; i < N2; ++i)
		if (arr[i])
			++cnt;
	printf("#primes <= 10000: %ld\n", cnt);

	for (; i < N3; ++i)
		if (arr[i])
			++cnt;
	printf("#primes <= 100000: %ld\n", cnt);

	for (; i < N4; ++i)
		if (arr[i])
			++cnt;
	printf("#primes <= 1000000: %ld\n", cnt);

	free(arr);
}

void sieve_int(long n, int *arr){
  long i, j;

	for (i = 2; i < n; ++i)
		arr[i] = 1;
	for (i = 2; i < n; ++i)
		if (arr[i])
			for (j = i; i*j < n; ++j)
				arr[i*j] = 0;
}