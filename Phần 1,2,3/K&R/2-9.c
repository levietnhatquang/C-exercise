/*
 * Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the
 * rightmost 1-bit in x. Explain why. Use this observation to write a faster ver-
 * version of bitcount.
 */
#include<stdio.h>

int bit_count(int x);
void printf_b(int x);

int main(){
	int x = 123865;
	printf_b(x);
	printf("number of '1' bit: %d\n", bit_count(x));
}

int bit_count(int x){
	int counter = 0;
	while(x != 0){
		x &= (x-1);
		counter++;
	}
	return counter;
}
void printf_b(int x){
	while (x) {
		if (x & 1)
		    printf("1");
		else
		    printf("0");
		x >>= 1; //x = x >> 1;
	}
	printf("\n");
}
//output:
/*
quanglvn@quanglvn:~/thuviec/123$ gcc 2-9.c -o 2-9
quanglvn@quanglvn:~/thuviec/123$ ./2-9
10011011110001111
number of '1' bit: 11
*/