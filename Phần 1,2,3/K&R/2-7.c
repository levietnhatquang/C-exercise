/*
 * Exercise 2-7. Write a function invert(x, p, n) that returns x with the n bits
 * that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving
 * the others unchanged.
 */

#include<stdio.h>

unsigned invert(unsigned x, int p, int n);

int main(void){
	printf("%u",(unsigned)invert((unsigned)8,(int)3,(int)3));
	return 0;
}

unsigned invert(unsigned x, int p, int n)
{
	//Get n bit from position p:
	unsigned int a = (~(~0 << n) << (p + 1 - n));
    return x ^ a;
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 2-7.c -o 2-7
 * quanglvn@quanglvn:~/thuviec/123$ ./2-7
 * 6
 */