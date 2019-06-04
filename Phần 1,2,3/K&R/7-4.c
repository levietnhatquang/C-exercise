#include <stdio.h>
#include <stdarg.h>

void my_scanf(char *fmt, ...);

int main(){
	char s[100];
	int n;
	my_scanf("%s %d", s, &n);
	printf("%s %d\n", s, n);
	return 0;
}

void my_scanf(char *fmt, ...)
{
	va_list ap;
	int *ival;
	char *cval;
	va_start(ap, fmt);
	for (char *p = fmt; *p; p++){
		if (*p != '%'){
			continue;
		}
		switch (*++p){
		case 'd':
			ival = va_arg(ap, int *);
			scanf("%d", ival);
		case 's':
			cval = va_arg(ap, char *);
			scanf("%s", cval);
		}
	}
	va_end(ap);
}
/* 
 * output
 *
 * quanglvn@Quangs-MacBook:~/Desktop$ gcc 7-4.c -o 7-4
 * quanglvn@Quangs-MacBook:~/Desktop$ ./7-4
 * Excersise: 74
 * Excersise: 74
 */