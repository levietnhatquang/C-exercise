/* 
 * va_list	create pointer to arg
 * va_start point the pointer to 1st arg
 * va_arg	define data type for each arg pointed by the pointer
 * va_end	clean up pointer
 */

#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main(){
	char *s = "100";
	minprintf("minprintf(\"%s %s\", 1, 1);\n%d %i\n", "%d", "%i", 1, 1);
	minprintf("minprintf(\"%s\", 1);\n%o\n", "%o", 1);
	minprintf("minprintf(\"%s %s\", 1, 1);\n%x %X\n", "%x", "%X", 1, 1);
	minprintf("minprintf(\"%s\", 1);\n%u\n", "%u", 1);
	minprintf("minprintf(\"%s\", 100);\n%c\n", "%c", 100);
	minprintf("minprintf(\"%s\", s);\n%s\n", "%s", s);
	minprintf("minprintf(\"%s\", 1.0);\n%f\n", "%f", 1.0);
	minprintf("minprintf(\"%s %s\", 1, 1);\n%e %E\n", "%e", "%E", 1, 1);
	minprintf("minprintf(\"%s %s\", 1, 1);\n%g %G\n", "%g", "%G", 1, 1);
	return 0;
}

void minprintf(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++){
		if (*p != '%'){
			putchar(*p);
			continue;
		}
		switch (*++p){
		case 'd': case 'i':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'o':
			ival = va_arg(ap, int);
			printf("%o", ival);
			break;
		case 'x': case 'X':
			ival = va_arg(ap, int);
			printf("%x", ival);
			break;
		case 'u':
			ival = va_arg(ap, int);
			printf("%u", ival);
			break;
		case 'c':
			ival = va_arg(ap, int);
			printf("%c", ival);
			break;
		case 's':
			for (sval = va_arg(ap, char *); *sval; sval++)
				putchar(*sval);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 'e': case 'E':
			ival = va_arg(ap, double);
			printf("%d", ival);
			break;
		case 'g': case 'G':
			ival = va_arg(ap, double);
			printf("%d", ival);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);
}

/*
 * output
 *
 * quanglvn@Quangs-MacBook:~/Desktop$ gcc 7-3.c -o 7-3
 * quanglvn@Quangs-MacBook:~/Desktop$ ./7-3
 * minprintf("%d %i", 1, 1);
 * 1 1
 * minprintf("%o", 1);
 * 1
 * minprintf("%x %X", 1, 1);
 * 1 1
 * minprintf("%u", 1);
 * 1
 * minprintf("%c", 100);
 * d
 * minprintf("%s", s);
 * 100
 * minprintf("%f", 1.0);
 * 1.000000
 * minprintf("%e %E", 1, 1);
 * 1.000000e+00 2.113707E-314
 * minprintf("%g %G", 1, 1);
 * 1 2.11371E-314
 */