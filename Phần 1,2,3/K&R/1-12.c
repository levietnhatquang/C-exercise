/*
 * Exercise 1-12. Write a program that prints its input one word per line.
 */

#include<stdio.h>
#define A 65
#define Z 90
#define a 97
#define z 122
int main(){
	int c, state;
	state = 0;
	while ((c = getchar()) != EOF){
		if ( (A <= c && c <= Z) || (a <= c && c <= z)){
			putchar(c);
			state = 1;
		}
		else{
			if (state){
				putchar('\n');
				state = 0;
			}
		}
	}
	return 0;
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-12.c -o 1-12
 * quanglvn@quanglvn:~/thuviec/123$ ./1-12
 * The fourth in our series of useful programs counts lines, words, and charac-
 * characters, with the loose definition that a word is any sequence of characters that
 * does not contain a blank, tab or newline. This is a bare-bones version of the
 * UNIX program we.
 * The
 * #include <stdio.h>
 * #define IN 1 // inside a fourth word
 * The
 * fourth
 * in
 * our
 * series
 * of
 * useful
 * programs
 * counts
 * lines
 * words
 * and
 * charac
 * characters
 * with
 * the
 * loose
 * definition
 * that
 * a
 * word
 * is
 * any
 * sequence
 * of
 * characters
 * that
 * does
 * not
 * contain
 * a
 * blank
 * tab
 * or
 * newline
 * This
 * is
 * a
 * bare
 * bones
 * version
 * of
 * the
 * UNIX
 * program
 * we
 * include
 * stdio
 * h
 * define
 * IN
 * inside
 * a
 * word
 */