/*
 * Exercise 2-8. Write a function rightrot(x,p) that returns the value of the
 * integer x rotated to the right by n bit positions.
 */
#include<stdio.h>
#include<math.h>

int rightrot(int x, int p);
void printf_b(int x);
unsigned countBits(unsigned int number);

int main(){
	printf("Before: ");
	int x = 76123;
	int p = 7;
	printf_b(x);
	int r = rightrot(x, p);
	printf("After rotating by p: ");
	printf_b(r);
	return 0;
}

int rightrot(int x, int p){
	return ((x << p)|(x >> (countBits(x) - p))) & (~(~0 << countBits(x))); 
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
unsigned countBits(unsigned int number){      
      return (int)log2(number)+1; 
} 
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 2-8.c -o 2-8 -lm
 * quanglvn@quanglvn:~/thuviec/123$ ./2-8
 * Before: 11011010100101001
 * After rotating by p: 0101001110110101
 */