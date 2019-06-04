/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing. Good possibilities include get line
 * (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4),
 * reverse (Chapter 3), and strindex and getop (Chapter 4).
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define MAXCHAR 1000

void itoa(int n, char *s, int width);
void reverse(char *s);

int main(){
	char s[MAXCHAR];
	printf("INT_MIN: %d\n", INT_MIN);
	int n = INT_MIN;
	itoa(n, s, 15);
	printf("%s\n", s);
	return 0;
}


void itoa(int n, char *s, int width)
{
	int i, sign;

	sign = n;

	i = 0;
	do { 
		*(s + i++) = abs(n%10) + '0'; 
	} while (n /= 10);
	if (sign < 0)
		*(s + i++) = '-';
	while(i < width){
		*(s + i++) = ' ';
	}
	s[i] = '\0';
	reverse(s);
}
void reverse(char *s)
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = *(s + i);
		*(s + i) = *(s + j);
		*(s + j) = c;
	}
}