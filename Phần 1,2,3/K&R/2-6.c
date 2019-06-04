/*
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
 * bits that begin at position p set to the rightmost n bits of y, leaving the other
 * bits unchanged.
 *
 *  NOTE
 *
 * & 	bitwise AND
 * | 	bitwise inclusive OR
 * ^	bitwise exclusive OR
 * << 	left shift
 * >>	right shift
 * ~	one's complement (unary)
 */

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void){	
	int x = 255;
	int p = 3;
	int n = 4;
	int y = 0;
	printf("setbits(%u, %d, %d, %u) = %u\n", x, p, n, y, setbits(x, p, n, y));
	return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	int a = (~0 << (p + 1)) | (~(~0 << (p + 1 - n)));
	int b = x & a;
	int c = (y & ~(~0 << n)) << (p + 1 - n);
	return b | c;
}
