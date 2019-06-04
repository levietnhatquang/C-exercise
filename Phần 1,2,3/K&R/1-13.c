/*
 * Exercise 1-13. Write a program to print a histogram of the lengths of words in
 * its input. It is easy to draw the histogram with the bars horizontal; a vertical
 * orientation is more challenging.
 */

#include<stdio.h>
#define A 65
#define Z 90
#define a 97
#define z 122
#define MAX 20
int main(){
	int c, state, count;
	state = 0;
	count = 0;
	char Lenths[MAX];
	for (int i = 0; i < MAX; i++)
		Lenths[i] = 0;
	while ((c = getchar()) != EOF){
		if ( (A <= c && c <= Z) || (a <= c && c <= z)){
			count ++;
			state = 1;
		}
		else{
			if (state){
				Lenths[count]++;
				count = 0;
				state = 0;
			}
		}
	}
	for (int i = 0; i < MAX; i++){
		printf("%d:",i);
		for(int j = 0; j < Lenths[i]; j++)
			printf(".");
		printf("\n");
	}
	return 0;
}
/*output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-13.c -o 1-13
 * quanglvn@quanglvn:~/thuviec/123$ ./1-13
 * In C, a function is equivalent to a subroutine or function in Fortran, or a
 * procedure or function in Pascal. A function provides a convenient way to
 * encapsulate some computation, which can then be used without worrying about
 * its implementation. With properly designed functions, it is possible to ignore
 * how a job is done; knowing what is done is sufficient. C makes the use of func-
 * functions easy, convenient and efficient; you will often see a short function defined
 * and called only once, just because it clarifies some piece of code.
 * 0:
 * 1:.........
 * 2:...................
 * 3:...........
 * 4:...............
 * 5:......
 * 6:...
 * 7:.....
 * 8:..........
 * 9:.....
 * 10:.....
 * 11:..
 * 12:
 * 13:
 * 14:.
 * 15:
 * 16:
 * 17:
 * 18:
 * 19:
 */