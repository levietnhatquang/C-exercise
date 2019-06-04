/*
 * Exercise 1-8. Write a program to count blanks, tabs, and newlines.
 */

#include<stdio.h>
int main(){
	int b, t, n, c;
	b = 0;
	t = 0;
	n = 0;
	while((c = getchar()) != EOF){
		if (c == '\b')
			b++;
		else if(c == '\t')
			t++;
		else if (c == '\n')
			n++;
	}
	printf("Number of blanks: %d", b);
	printf("Number of tabs: %d", t);
	printf("Number of newlines: %d", n);
	return 0;
}
/*output:
 *
 */