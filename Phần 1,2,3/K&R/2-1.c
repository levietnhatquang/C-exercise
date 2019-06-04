/*
 * Exercise 2-1. Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing appropriate
 * values from standard headers and by direct computation. Harder if you com-
 * compute them: determine the ranges of the various floating-point types.
 *
 *  NOTE
 *
 * char 	a single byte, capable of holding one character
 * 		in the local character set.
 * int 	an integer, typically reflecting the natural size
 * 		of integers on the host machine,
 * float 	single-precision floating point,
 * double 	double-precision floating point.
 * short int sh;
 * long int counter;
 * short is at least 16 bits, long at least 32 bits, and int is somewhere bw short and long
 */

#include <stdio.h>
#include <limits.h>


int main(void){
  printf("Signed char: \tranging from %d to %d\n", SCHAR_MIN, SCHAR_MAX);
  printf("Unsigned char: \tranging from 0 to %d\n", UCHAR_MAX);
  printf("Signed short int: \tranging from %d to %d\n", SHRT_MIN, SHRT_MAX);
  printf("Unsigned short int: \tranging from 0 to %d\n", USHRT_MAX);
  printf("Signed int: \tranging from %d to %d\n", INT_MIN, INT_MAX);
  printf("Unsigned int: \tranging from 0 to %d\n", UINT_MAX);
  printf("Signed long: \tranging from %ld to %ld\n", LONG_MIN, LONG_MAX);
  printf("Unsigned long: \tranging from 0 to %ld\n", ULONG_MAX);
  return 0;
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 2-1.c -o 2-1
 * quanglvn@quanglvn:~/thuviec/123$ ./2-1
 * Signed char: 	ranging from -128 to 127
 * Unsigned char: 	ranging from 0 to 255
 * Signed short int: 	ranging from -32768 to 32767
 * Unsigned short int: 	ranging from 0 to 65535
 * Signed int: 	ranging from -2147483648 to 2147483647
 * Unsigned int: 	ranging from 0 to -1
 * Signed long: 	ranging from -9223372036854775808 to 9223372036854775807
 * Unsigned long: 	ranging from 0 to -1
 */