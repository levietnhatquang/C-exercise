/*
 * Exercise 5-3. Write a pointer version of the function Strcat that we showed
 * in Chapter 2: streat (s,t) copies the string t to the end of s.
 */

#include <stdio.h>

#define MAXCHAR 1024

void Strcat(char *s, char *t);

int main(void)
{
  char s1[MAXCHAR] = "abcdef"; //array declaration
  char s2[MAXCHAR] = "123";

  printf("s1: '%s'\n", s1);
  printf("s2: '%s'\n", s2);
 
  Strcat(s1, s2);
  printf("s1 concaternates s2: '%s'\n", s1);

  return 0;
}

void Strcat(char *s, char *t)
{
  while(*s != '\0'){
    s++;
  }
  while(*s++ = *t++)
  	;
}
/* 
 * output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-3.c -o 5-3
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-3
 * s1: 'abcdef'
 * s2: '123'
 * s1 concaternates s2: 'abcdef123'
 */
