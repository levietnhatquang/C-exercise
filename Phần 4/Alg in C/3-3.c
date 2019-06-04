/* 
 * 3.3 Test the random-number generator on your system by generating N
 * random numbers of type double between 0 and 1, transforming them to
 * integers between 0 and r - 1 by multiplying by r and truncating the result,
 * and computing the average and standard deviation for r = 10, 100, and 1000
 * and N = 103 , 104 , 105 , and 106 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sum(double arr[]);
double average(double arr[]);
double standard_deviation(double arr[]);
double rand_double(double min, double max);
double *A = NULL;
int R, N;

int main(int argc, char *argv[]){
	if (argv[1] == NULL && argv[2] == NULL){
		printf("%s\n", "Wrong format, use ./3-3 R N");
		return EXIT_FAILURE;
	}
	R = atoi(argv[1]);
	N = atoi(argv[2]);
	A = (double*)malloc(N * sizeof(double));

	for (int i = 0; i < N; i++)
		A[i] = (int)(rand_double(0, 1) * R);
	printf("Average: %f\n", average(A));
	printf("Standard deviation: %f\n", standard_deviation(A));
	return 0;
}

double rand_double(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

double sum(double arr[]) 
{ 
    double sum = 0;  
    for (int i = 0; i < N; i++) 
    	sum += arr[i]; 
    return sum; 
}

double average(double arr[])
{
	return sum(arr) / N;
}

double standard_deviation(double arr[])
{
	double m = average(arr);
	double t = 0;
	for (int i = 0; i < N; i++){
		t += pow(arr[i] - m, 2);
	}
	return sqrt(t / N);
}
