/*
 * Exercise 5-19. Modify undcl so that it does not add redundant parentheses to
 * declarations.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getch.h"

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

static int gettoken(void);

static int tokentype; /* type of last token */
static int oldtoken; /* previous tokentype */
static char token[MAXTOKEN]; /* last token string */
static char name[MAXTOKEN]; /* identifier name */
static char datatype[MAXTOKEN]; /* data type = char, int, etc. */
static char out[1000]; /* output string */

int main()
{
	int type;
	char temp[MAXTOKEN];
	int state = 0;
	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS){
				if(state){
					sprintf(temp, "(%s)", out);
					strcpy(out, temp);
					state = 0;
				}
				strcat(out, token);
			}
			else if (type == '*') {
				state = 1;
				sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				if(state){
					sprintf(temp, "(%s)", out);
					strcpy(out, temp);
					state = 0;
				}
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else{
				printf("invalid input at %s\n", token);
			}
		printf("%s\n", out);
	}	
return 0;
}

int gettoken(void) /* return next token */
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c =='('){
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-19.c getch.c -o 5-19
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-19
 * x()***char
 * char (***x())
 * x()*[]*()char
 * char (*(*x())[])()
 */