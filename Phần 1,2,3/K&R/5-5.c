/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strnemp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy (s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 */

#include <stdio.h>

#define MAX 20

void Strncpy(char *s, const char *t, int n);
void Strncat(char *s, const char *t, int n);
int Strncmp(const char *s, const char *t, int n);

int main(void){
	char s[MAX] = "abcdfgh";
	char *t = "123";

	Strncat(s, t, 3);
	printf("Strncat: '%s'\n", s);
	Strncpy(s, t, 4);
	printf("Strncpy: '%s'\n", s);
	printf("Strncmp: '%s'\n", Strncmp(s, t, 4) == 0 ? "yes" : "no");

	return 0;
}

void Strncpy(char *s, const char *t, int n)
{
	for (int i = 0; i < n; i++)
		*(s + i) = *(t + i) ? *(t + i) : '\0';
}

void Strncat(char *s, const char *t, int n)
{
	int i;
	while (*++s)
		;
	for (i = 0; i < n && *(t + i); i++)
		*(s + i) = *(t + i);
	*(s + i) = '\0';
}

int Strncmp(const char *s, const char *t, int n)
{
	int i;
	for (int i = 0; i < n && *(s + i) == *(t + i) && *(s + i); i++)
		;
	if (*(s + i) != *(t + i))
		 return *(s + i) - *(t + i);
	return 0;
}

/* output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-5.c -o 5-5
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-5
 * Strncat: 'abcdfgh123'
 * Strncpy: '123'
 * Strncmp: 'no'
 */