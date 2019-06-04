/*
 * Exercise 5-18. Make del recover from input errors,
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getch.h"

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

static void dcl(void);
static void dirdcl(void);
static int gettoken(void);

static int tokentype; /* type of last token */
static int oldtoken; /* previous tokentype */
static char token[MAXTOKEN]; /* last token string */
static char name[MAXTOKEN]; /* identifier name */
static char datatype[MAXTOKEN]; /* data type = char, int, etc. */
static char out[1000]; /* output string */

int main(void){
	while (gettoken() != EOF) { /* 1st token on line */		
		strcpy(datatype, token); /* pull data type */
	out[0] = '\0';
	dcl(); /* parse rest of line */
	if (tokentype != '\n')
		printf("syntax error\n");
	printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

void dcl(void){
	int ns;
	for (ns = 0; gettoken() == '*';)
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

void dirdcl(void){
	int type;
	if (tokentype =='('){ /* ( del ) */
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	} else if (tokentype == NAME) /* variable name */
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
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
/*output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-18.c getch.c -o 5-18
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-18
 */