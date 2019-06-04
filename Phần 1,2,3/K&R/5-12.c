/*
 * Exercise 5-12. Extend entab and detab to accept the shorthand
 * entab -m +n
 * to mean tab stops every n columns, starting at column m. Choose convenient
 * (for the user) default behavior.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define N 8 //tab stops at every 8 blanks
#define MAXCHAR 1000

int main(int argc, char **argv){
	if(!(!strcmp(*(argv + 1), "entab") &&  **(argv + 2) == '-' && **(argv + 3) == '+'
		&& isdigit(*(*(argv + 2) + 1)) && isdigit(*(*(argv + 3) + 1)))){
		printf("Shorthand not support!\n");
		return 0;
	}
	int m = *(*(argv + 2) + 1) - '0';
	int n = *(*(argv + 3) + 1) - '0';
	int c;
	int counter = 0;
	while ((c = getchar()) != EOF){
		if (counter++ >= m && c == '\t')
			for (int i = 0; i < n; i++)
				putchar(' ');
		else
			putchar(c);
		if(c == '\n')
			counter = 0;
	}
	return 0;
}
/*output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-12.c -o 5-12
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-12 entab -2 +4
 * 1	22		333		4444	55555
 * 1	22    333    4444    55555
 */