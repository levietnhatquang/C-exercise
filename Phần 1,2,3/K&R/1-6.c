/*
 * Exercise 1-6. Verify that the expression getchar () 1= EOF is 0 or 1.
 */

#include <stdio.h>
/* copy input to output; 2nd version */
int main(){
	int c;
	while ((c = getchar()) != EOF){
		int verify = (c = getchar() != EOF ? 1 : 0);
		printf("expresion getchar() != EOF is %d\n", verify);
		putchar(c);
	}
	return 0;
}

/* 
 * output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-6.c -o 1-6
 * quanglvn@quanglvn:~/thuviec/123$ ./1-6
 * 
 * 123
 * expresion getchar() != EOF is 1
 * 123
 * expresion getchar() != EOF is 1
 * ^C
 *
 * comment
 *
 * c must be a type big enough to hould any value that getchar() return
 */