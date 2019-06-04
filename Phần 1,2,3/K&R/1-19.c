/*
 * Exercise 1-19. Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverses its input a line at a time.
 */

#include <stdio.h>
#define MAXLINE 100 /* maximum input line size */
#define MAXCHAR 100

int Getline(char *from, char *to);

int main(){
	char Reserve[MAXLINE][MAXCHAR];
	char tmp[MAXCHAR];
	int c, l, ch;
	l = 0;
	ch = 0;
	for(int i = 0; i<MAXLINE; i++)
		Reserve[i][0] = '\0';
	while((c = getchar()) != EOF){
		tmp[ch++] = c;
		if (c == '\n'){
			Getline(tmp, Reserve[l++]);
			ch = 0;
		}
	}
	for(int i = 0; i<MAXLINE; i++){
		if (Reserve[i][0] == '\0')
			continue;
		for(int j=0; j<MAXCHAR; j++){
			printf("%c", Reserve[i][j]);
			if (Reserve[i][j] == '\n')
				break;
		}
	}
	return 0;
}

int Getline (char *from, char *to){
	int ch = 0;
	while(from[ch] != '\n'){
		to[ch] = from[ch];
		ch++;
	}
	to[ch] = from[ch];
}

/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-19.c -o 1-19
 * quanglvn@quanglvn:~/thuviec/123$ ./1-19
 * 38475 (*$&%
 * JHR(&$(*%
 * 8475
 * 38475 (*$&%
 * JHR(&$(*%
 * 8475
 */