/*
 * 	Add commands 
 * 		(1) to print the top element of the stack without popping
 * 		(2) to duplicate top element
 * 		(3) to swap the top two elements 
 * 		(4) to clear the stack
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER 0
#define MAXVAL 100
#define BUFSIZE 100

int getop(char *);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void view(void);
void view_top(void); //(1)
void duplicate_top(void); //(2)
void swap_top(void); //(3)
void clear(void); //(4)

int main(){
    int type;
    double op2;
    char s[MAXOP];

    printf("Pushing 1, 2, 3 to stack ...\n");
    push(1);
    push(2);
    push(3);
    view();
    printf("Swapping top two elements ...\n");
    swap_top();
    view();
    printf("Duplicating top element ...\n");
    duplicate_top();
    view();
    printf("Clearing stack ...\n");
    clear();
    view();

    while((type = getop(s)) != EOF)
    {
    	view();
    	view_top();
        switch(type){
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if(op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if(op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: division by zero\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

int bufp = 0;
char buf[BUFSIZE];
int sp = 0;
double val[MAXVAL];


void push(double f){
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void){
    if(sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        exit(1);
        //return 0.0;
    }
}

int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getop(char *s){
    int i, c, d;
    while((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    if(!isdigit(c) && c != '.' && c != '-')
        return c;
    if(c == '-')
    {
        d = getch();
        if(d == ' ')
            return c;
        else
            ungetch(d);
    }
    i = 0;
    if(isdigit(c) || c == '-')
        while(isdigit(s[++i] = c = getch()));
    if(c == '.')
        while(isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if(c != EOF)
        ungetch(c);
    return NUMBER;
}

void view(void){
	int i;
	printf("\nstack:\n");
	if(val[sp - 1] == '\0')
		printf("Stack empty\n");
	for(i = sp - 1; i >= 0; i--)
		printf("%lf\n", val[i]);
}

void view_top(void){
	if(val[sp - 1] != '\0')
		printf("Top stack: %lf\n", val[sp - 1]);
	else
		printf("Top stack: Not available");
}

void duplicate_top(void){
	val[sp] = val[sp - 1];
	sp++;
}
void swap_top(void){
	if(sp >= 2){
		int tmp;
		tmp = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = tmp;
	}
	else
		printf("Cannot swap, Stack has only one element\n");
	
}
void clear(void){
	sp = 0;
}
/*output
 *
 * Quangs-MacBook:123 quanglvn$ gcc 4-4.c -o 4-4
 * Quangs-MacBook:123 quanglvn$ ./4-4
 * Pushing 1, 2, 3 to stack ...
 * 
 * stack:
 * 3.000000
 * 2.000000
 * 1.000000
 * Swapping top two elements ...
 * 
 * stack:
 * 2.000000
 * 3.000000
 * 1.000000
 * Duplicating top element ...
 * 
 * stack:
 * 2.000000
 * 2.000000
 * 3.000000
 * 1.000000
 * Clearing stack ...
 * 
 * stack:
 * Stack empty
 * 1 2 +
 * 
 * stack:
 * Stack empty
 * Top stack: Not available
 * stack:
 * 1.000000
 * Top stack: 1.000000
 * 
 * stack:
 * 2.000000
 * 1.000000
 * Top stack: 2.000000
 * 
 * stack:
 * 3.000000
 * Top stack: 3.000000
 * 	3
 */
