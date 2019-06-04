/*
 * Exercise 3-6. Write a version of itoa that accepts three arguments instead of
 * two. The third argument is a minimum field width; the converted number must
 * be padded with blanks on the left if necessary to make it wide enough.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define MAXCHAR 1000

void itoa(int n, char s[], int width);
void reverse(char s[]);

int main(){
	char s[MAXCHAR];
	printf("INT_MIN: %d\n", INT_MIN);
	int n = INT_MIN;
	itoa(n, s, 15);
	printf("%s\n", s);
	return 0;
}


void itoa(int n, char s[], int width)
{
	int i, sign;

	sign = n;

	i = 0;
	do { 
		s[i++] = abs(n%10) + '0'; 
	} while (n /= 10);
	if (sign < 0)
		s[i++] = '-';
	while(i < width){
		s[i++] = ' ';
	}
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
/*output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 3-6.c -o 3-6
 * quanglvn@quanglvn:~/thuviec/123$ ./3-6
 * INT_MIN: -2147483648
 *     -2147483648
 */