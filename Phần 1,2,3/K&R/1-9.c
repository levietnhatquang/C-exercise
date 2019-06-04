/*
 * Exercise 1-9. Write a program to copy its input to its output, replacing each
 * string of one or more blanks by a single blank.
 */
#include<stdio.h>
int main(){
	int c, flag;
	flag = 0;
	while((c = getchar()) != EOF){
		if ((c == ' ') && (flag == 1))
			c = c;
		else if (c == ' '){
			flag = 1;
			putchar(c);
		}
		else{
			flag = 0;
			putchar(c);
		}
	}
}
/*
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-9.c -o 1-9
 * quanglvn@quanglvn:~/thuviec/123$ ./1-9
 *  a  b   cdef
 *  a b cdef
 */