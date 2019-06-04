/*
 * Exercise 1-10. Write a program to copy its input to its output, replacing each
 * tab by \t, each backspace by \b, and each backslash by \\. This makes tabs
 * and backspaces visible in an unambiguous way.
 */

#include<stdio.h>
int main(){
	int c;
	while((c = getchar()) != EOF){
		if(c == '\t' || c == ' ')
			c = '\\';
		else if (c == '\\'){
			c = '\\';
			putchar(c);
		}
		putchar(c);
	}
	return 0;
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-10.c -o 1-10
 * quanglvn@quanglvn:~/thuviec/123$ ./1-10
 * nh at	q\ua\\ng
 * nh\at\q\\ua\\\\ng
 */