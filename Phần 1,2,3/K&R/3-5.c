/*
 * Exercise 3-5. Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s. In particular,
 * itob(n,s, 16) formats n as a hexadecimal integer in s.
 *
 * 
 * NOTE 
 *
 * currently work for positive number only
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXCHAR 1000

void itob(unsigned int n, char *s, int b);
void reverse(char *s);

int main(){
	char s[MAXCHAR];
	unsigned int n = 100;
	itob(n, s, 10);
	printf("b = 10: %s\n", s);
	itob(n, s, 2);
	printf("b = 2: %s\n", s);
	itob(n, s, 16);
	printf("b = 16: %s\n", s);
	return 0;
}

void itob(unsigned int n, char *s, int b)
{
	int i, sign;
	sign = n;
	i = 0;
	do { 
		s[i++] = abs(n%b) + '0'; 
	} while (n /= b);
	s[i] = '\0';
	reverse(s);
}
void reverse(char *s)
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
/* output:
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 3-5.c -o 3-5
 * quanglvn@quanglvn:~/thuviec/123$ ./3-5
 * b = 10: 100
 * b = 2: 1100100
 * b = 16: 64
 */