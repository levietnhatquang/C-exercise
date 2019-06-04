/*
 * Exercise 1-7. Write a program to print the value of EOF. 
 */

#include<stdio.h>
int main(){
	printf("%d %1.1f %c\n", EOF, EOF, EOF);
	return 0;
}

/* 
 * output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-7.c -o 1-7
 * 1-7.c: In function ‘main’:
 * 1-7.c:3:9: warning: format ‘%f’ expects argument of type ‘double’, but argument 3 has type ‘int’ [-Wformat=]
 *   printf("%d %1.1f %c\n", EOF, EOF, EOF);
 *          ^
 * quanglvn@quanglvn:~/thuviec/123$ ./1-7
 * -1 0.0 �
 */