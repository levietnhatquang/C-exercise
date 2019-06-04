/*
 * Exercise 1-14. Write a program to print a histogram of the frequencies of dif-
 * different characters in its input.
 */
#include<stdio.h>
#define MAX 128
int main(){
	char ascii[MAX];
	int c;
	for (int i = 0; i < MAX; i++)
		ascii[i] = 0;
	while((c = getchar()) != EOF){
		ascii[c] = ascii[c] + 1;
	}
	printf("\n");
	for (int i = 0; i < MAX; i++){
		putchar(i);
		putchar(':');
		for (int j = 0; j < ascii[i]; j++){
			putchar('.');
		}
		putchar('\n');
	}
	return 0;
}
/* utput
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-13.c -o 1-13
 * quanglvn@quanglvn:~/thuviec/123$ ./1-13
 * In C, a function is equivalent to a subroutine or function in Fortran, or a
 * procedure or function in Pascal. A function provides a convenient way to
 * encapsulate some computation, which can then be used without worrying about
 * its implementation. With properly designed functions, it is possible to ignore
 * how a job is done; knowing what is done is sufficient. C makes the use of func-
 * functions easy, convenient and efficient; you will often see a short function defined
 * and called only once, just because it clarifies some piece of code.
 * So far we have used only functions like printf, getchar, and putchar
 * that have been provided for us; now it's time to write a few of our own. Since C
 * has no exponentiation operator like the ** of Fortran, let us illustrate the
 * mechanics of function definition by writing a function power (m,n) to raise an
 * integer m to a positive integer power n. That is, the value of power B,5) is
 * 32. This function is not a practical exponentiation routine, since it handles only
 * positive powers of small integers, but it's good enough for illustration. (The
 * standard library contains a function pow(x,y) that computes xy.)
 * Here is the function power and a main program to exercise it, so you can
 * see the whole structure at once.
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * 	:
 * 
 * :................
 * 
 * :
 * 
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * :
 * !:
 * ":
 * #:
 * $:
 * %:
 * &:
 * ':..
 * (:...
 * ):....
 * *:..
 * +:
 * ,:................
 * -:.
 * .:..........
 * /:
 * 0:
 * 1:
 * 2:.
 * 3:.
 * 4:
 * 5:.
 * 6:
 * 7:
 * 8:
 * 9:
 * ::
 * ;:...
 * <:
 * =:
 * >:
 * ?:
 * @:
 * A:.
 * B:.
 * C:...
 * D:
 * E:
 * F:..
 * G:
 * H:.
 * I:.
 * J:
 * K:
 * L:
 * M:
 * N:
 * O:
 * P:.
 * Q:
 * R:
 * S:..
 * T:...
 * U:
 * V:
 * W:.
 * X:
 * Y:
 * Z:
 * [:
 * \:
 * ]:
 * ^:
 * _:
 * `:
 * a:................................................................
 * b:..........
 * c:............................................
 * d:.......................
 * e:.........................................................................................................
 * f:..................................
 * g:............
 * h:............................
 * i:............................................................................................
 * j:..
 * k:....
 * l:............................
 * n:...................................................................................................
 * p:..........................
 * r:....................................................
 * s:.........................................................
 * t:............................................................................................
 * u:...........................................
 * v:..........
 * w:.....................
 * x:.....
 * y:.............
 * z:
 * {:
 * |:
 * }:
 * ~:
 * :
 */