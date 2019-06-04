/*
 * Exercise 5-1. As written, getint treats a + or - not followed by a digit as a
 * valid representation of zero. Fix it to push such a character back on the input.
 */
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define BUFSIZE 100
#define TESTNUM 10

int getch(void);
void ungetch(int);
int getint(int *pn);

int main(){
	int i = 0;
	int tmp;
	while(i++ < TESTNUM){
		if(getint(&tmp))
			printf("Number got: %d\n", tmp);
		else
			printf("Not a number!\n");
		
	}
	return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn){
	int c, sign;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') { //skipped to non-space character
		ungetch(c); /* it's not a number */
		return 0;
	}
	sign = (c =='-')? -1 : 1;
	if (c == '+' || c == '-'){
		c = getch(); //check if after sign character is digit or not
		if(isdigit(c) == 0){  // if not pushed back
			ungetch(sign == 1 ? '+' : '-');
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn =10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int bufp = 0;
char buf[BUFSIZE];

int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
/*output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-1.c -o 5-1
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-1
 * 1
 * Number got: 1
 * 10
 * Number got: 10
 *   -235 +35
 * Number got: -235
 * Number got: 35
 * abc
 * Not a number!
 */