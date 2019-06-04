/*
 * Exercise 1-1. Run the "hello, world" program on your system. Experiment
 * with leaving out parts of the program, to see what error messages you get.
 */

#include <stdio.h>
main(){
	printf("hello, ");
	printf("world");
	printf("\n");
}

/* output:
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-1.c -o 1-1
 * 1-1.c:2:1: warning: return type defaults to ‘int’ [-Wimplicit-int]
 *  main()
 *  ^
 * quanglvn@quanglvn:~/thuviec/123$ ./1-1
 * hello, world
 *comment:
 *
 * 	gcc automatically set return type to int => no error
 */