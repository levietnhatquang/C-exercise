/*
 * Exercise 5-2. Write get float, the floating-point analog of getint. What
 * type does getfloat return as its function value? => still int
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define BUFSIZE 100
#define TESTNUM 10

int getch(void);
void ungetch(int);
int getfloat(double *pn);

int main(){
	int i = 0;
	double tmp;
	while(i++ < TESTNUM){
		if(getfloat(&tmp))
			printf("Number got: %f\n", tmp);
		else
			printf("Not a number!\n");
		
	}
	return 0;
}

/* getint: get next integer from input into *pn */
int getfloat(double *pn){
	int c, sign, counter = 0, flag = 0; //flag = 1 => after '.'
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

	for (*pn = 0; isdigit(c) || c == '.'; c = getch()){
		if (c == '.'){
			flag = 1;
			continue;
		}
		if(flag){
			counter++;
			*pn =10 * *pn + (c - '0');
		}
		else
			*pn =10 * *pn + (c - '0');
	}
	while(counter-- > 0)
		*pn = *pn / 10;

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

/* output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-2.c -o 5-2
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-2
 * 1
 * Number got: 1.000000
 * 1.2
 * Number got: 1.200000
 * -13 +3.5 - 16.1
 * Number got: -13.000000
 * Number got: 3.500000
 * Not a number!
 * Number got: -16.100000
 */