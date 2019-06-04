/*
 * Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is 10, let us say, but it can be changed by an optional
 * argument, so that
 * tail -n
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or the value of n. Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting program of
 * Section 5.6, not in a two-dimensional array of fixed size.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXCHAR 2048

void tail(char *s, int n, int idx);

int main(int argc, char *argv[]){
	char buffer[MAXCHAR];
	int l = 0;
	int c;
	int n = 10;
	int i = 0;
	if (argc == 2 && **(argv + 1) == '-')
		n = atoi(*(argv + 1) + 1);
	else if (argc == 1)
		printf("Using default n = 10\n");
	while ((c = getchar()) != EOF){
		buffer[i++] = c;
		if(c == '\n'){
			l++;
		}
	}
	buffer[i] = '\0';
	if (l < n){
		printf("n is too large, using n = %d\n", l);
		tail(buffer, l, i);
	}
	else{
		tail(buffer, n, i);
	}
	return 0;
}

void tail(char *s, int n, int idx){
	while (idx-- >= 0 && n > 0){
		if (s[idx] == '\n')
			n--;
	}
	while(s[idx] != '\0')
		putchar(s[idx++]);

}
/*output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-13.c -o 5-13
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-13
 * Using default n = 10
 * a   
 * b
 * c
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 7
 * 8
 * 9
 * 10
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 7
 * 8
 * 9
 * 10
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-13 -3
 * abc
 * 1 
 * 2
 * 3 adf
 * 1
 * 2
 * 3 adf
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-13 -5
 * 1
 * 2
 * 3------- 
 * n is too large, using n = 3
 * 1
 * 2
 * 3-------
 */