/*
 * Exercise 5-10. Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a separate
 * argument. For example,
 * expr 2 3 4 + *
 * evaluates 2 x C+4).
 *
 *  note
 *
 * argc count:
 * exe file => first
 * null => last. For example:
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-10 1 2 3 4
 * 1: 1
 * 2: 2
 * 3: 3
 * 4: 4
 * 5: (null)
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STACK_SIZE 1024

void log_error(const char *msg);
void push(double x);
double pop(void);

int main(int argc, char **argv){
	int op1, op2;
	for (int i = 1; i < argc; i++){
		switch(**(argv + i)){
		case '+':
			push(pop() + pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
            if (op2 != 0.0)
                 push(fmod(pop(), op2));
            else
                printf("error: zero divisor\n");
			break;
		case '^':
			op2 = pop();
            op1 = pop();
            if (op1 == 0.0 && op2 <= 0)
                printf("if x = 0.0, y must be greater than 0\n");
            else
                push(pow(op1, op2));
			break;
		case 'e':
			push(exp(pop()));
			break;
		default:
			push(**(argv + i) - '0');
			break;
		}
	}
	printf("result: %f", pop());
	return 0;
}

double stack[STACK_SIZE];
int sp = 0;

void log_error(const char *msg){
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

void push(double x){
	if (sp < STACK_SIZE)
		stack[sp++] = x;
	else
		log_error("Stack is full!");
}

double pop(void){
	if (sp > 0)
		return stack[--sp];
	else
		log_error("Stack is empty!");
}
/*output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-10.c -o 5-10 -lm
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-10 2 e 3 4 + *
 * result: 62.000000
 */