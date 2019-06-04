/*
 * Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n equal
 * to -(2^(wordsize-1). Explain why not. Modify it to print that value correctly,
 * regardless of the machine on which it runs.
 *
 * 
 * EXPLAIN
 *
 * 	example: 8bit: -128 -> 127
 * 	the code use sign = -sign => sign = 128 => out of range
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define MAXCHAR 1000

void itoa(int n, char s[]);
void reverse(char s[]);

int main(){
	char s[MAXCHAR];
	printf("INT_MIN: %d\n", INT_MIN);
	int n = INT_MIN;
	itoa(n, s);
	printf("%s\n", s);
	return 0;
}


void itoa(int n, char s[])
{
	int i, sign;

	sign = n;

	i = 0;
	do { 
		s[i++] = abs(n%10) + '0'; 
	} while (n /= 10);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/*output:
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 3-4.c -o 3-4
 * quanglvn@quanglvn:~/thuviec/123$ ./3-4
 * INT_MIN: -2147483648
 * -2147483648
 */