/*
 * Exercise 5-4. Write the function Strend(s,t), which returns 1 if the String
 * t occurs at the end of the String s, and zero otherwise.
 */

#include<stdio.h>
#define MAXCHAR 100

int Strcmp(char *s, char *t);
int Strlen(char *s);
int Strend(char *s, char *t);

int main(){
	char s1[MAXCHAR] = "abcd1234";
	char s2[MAXCHAR] = "1234";
	printf("s1: %s\ns2: %s\nStrend: %s\n", s1, s2, (Strend(s1, s2)) ? "yes" : "no");
	char s3[MAXCHAR] = "abcd123";
	char s4[MAXCHAR] = "1234";
	printf("s1: %s\ns2: %s\nStrend: %s\n", s3, s4, (Strend(s3, s4)) ? "yes" : "no");
	return 0;
}

/* Strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int Strcmp(char *s, char *t)
{
	int i;
	//printf(" %d ", *s);printf(" %d ", *t);
	for (i = 0; s[i] == t[i]; i++){
		if (s[i] == '\0')
			return 0;
	}
	return s[i] - t[i];
}
/* Strlen: return length of String s */
int Strlen(char *s)
{
	char *p = s;
	while (*p != '\0')
		p++;
	return p - s;
}
//Strend(s,t), which returns 1 if the String
//t occurs at the end of the String s, and zero otherwise.
int Strend(char *s, char *t){
	int l1 = Strlen(s);
	//printf("%d",l1);
	int l2 = Strlen(t);
	//printf("%d",l2);
	//printf("%d",Strcmp(s + l2 - l1, t));
	if(l1 >= l2)
		return (Strcmp(s + l1 - l2, t) == 0) ? 1 : 0;
}
/* output:
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-4.c -o 5-4
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-4
 * s1: abcd1234
 * s2: 1234
 * Strend: yes
 * s1: abcd123
 * s2: 1234
 * Strend: no
 */