/*
 * Exercise 7-1. Write a program that converts upper case to lower or lower case
 * to upper, depending on the name it is invoked with, as found in argv [0]
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]){
	char *test = "Test Sample!";

	int mode = 0; //1: upper, 2: lower
	if (argc > 1){
		if (strcmp(*(argv + 1), "upper") == 0)
			mode = 1;
		if (strcmp(*(argv + 1), "lower") == 0)
			mode = 2;
	}
	int i = 0;
	if (mode == 1)
		while(*(test + i) != '\0')
			putchar(toupper(*(test + i++)));
	if (mode == 2)
		while(*(test + i) != '\0')
			putchar(tolower(*(test + i++)));
	return 0;
}

/* output
 *
 * quanglvn@quanglvn:~/thuviec$ gcc test.c -o test
 * quanglvn@quanglvn:~/thuviec$ ./test upper
 * TEST SAMPLE!
 * quanglvn@quanglvn:~/thuviec$ ./test lower
 * test sample!
 * quanglvn@quanglvn:~/thuviec$ ^C
 */