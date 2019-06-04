#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define MAXLINE 1000

void diff_line(char *lineone, char *linetwo, int linenumber);

int main(int argc, char *argv[])
{
  FILE *fp1, *fp2;
  char fp1_line[MAXLINE], fp2_line[MAXLINE];
  int i;

  if (argc != 3)
    {
      printf("Argument format: ./7-6.c file1 file2\n");
      exit(0);
    }

  fp1 = fopen( argv[1], "r" );
  if (!fp1){
      perror("Error");
      exit(EXIT_FAILURE);

    }

  fp2 = fopen( argv[2], "r" );
  if (!fp2){
      perror("Error");
      exit(EXIT_FAILURE);
    }
  i = 0;
  while ((fgets(fp1_line, MAXLINE, fp1) != NULL) && (fgets(fp2_line, MAXLINE, fp2) != NULL))
  {
    diff_line( fp1_line, fp2_line, i );
    i++;
  }

  return 0;
}

void diff_line( char *lineone, char *linetwo, int linenumber )
{
  if(strcmp (lineone, linetwo) < 0 || strcmp (lineone, linetwo) > 0)
    printf( "%d<%s\n%d>%s\n", linenumber, lineone, linenumber, linetwo);
}
/* output
 * quanglvn@quanglvn:~/1$ gcc 7-6.c -o 7-6
 * quanglvn@quanglvn:~/1$ ./7-6 2-8.c 2-9.c
 * 1<Exercise 2-8. Write a function rightrot(x,p) that returns the value of the
 * 
 * 1>Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the
 * 
 * 2<integer x rotated to the right by n bit positions.
 * 
 * 2>rightmost 1-bit in x. Explain why. Use this observation to write a faster ver-
 * 
 * 3<*
 * 
 * 3>version of bitcount.
 * 
 * 4<#include<stdio.h>
 * 
 * 4>*
 * 
 * 5<#include<math.h>
 * 
 * 5>#include<stdio.h>
 * 
 * 7<int rightrot(int x, int p);
 * 
 * 7>int bit_count(int x);
 * 
 * 9<unsigned countBits(unsigned int number);
 * 
 * 9>
 * 
 * 10<
 * 
 * 10>int main(){
 * 
 * 11<int main(){
 * 
 * 11>     int x = 123865;
 * 
 * 12<     printf("Before: ");
 * 
 * 12>     printf_b(x);
 * 
 * 13<     int x = 76123;
 * 
 * 13>     printf("number of '1' bit: %d\n", bit_count(x));
 * 
 * 14<     int p = 7;
 * 
 * 14>}
 * 
 * 15<     printf_b(x);
 * 
 * 15>
 * 
 * 16<     int r = rightrot(x, p);
 * 
 * 16>int bit_count(int x){
 * 
 * 17<     printf("After rotating by p: ");
 * 
 * 17>     int counter = 0;
 * 
 * 18<     printf_b(r);
 * 
 * 18>     while(x != 0){
 * 
 * 19<     return 0;
 * 
 * 19>             x &= (x-1);
 * 
 * 20<}
 * 
 * 20>             counter++;
 * 
 * 21<
 * 
 * 21>     }
 * 
 * 22<int rightrot(int x, int p){
 * 
 * 22>     return counter;
 * 
 * 23<     return ((x << p)|(x >> (countBits(x) - p))) & (~(~0 << countBits(x)));
 * 
 * 23>}
 * 
 * 24<}
 * 
 * 24>void printf_b(int x){
 * 
 * 25<void printf_b(int x){
 * 
 * 25>     while (x) {
 * 
 * 26<     while (x) {
 * 
 * 26>             if (x & 1)
 * 
 * 27<             if (x & 1)
 * 
 * 27>                 printf("1");
 * 
 * 28<                 printf("1");
 * 
 * 28>             else
 * 
 * 29<             else
 * 
 * 29>                 printf("0");
 * 
 * 30<                 printf("0");
 * 
 * 30>             x >>= 1; //x = x >> 1;
 * 
 * 31<             x >>= 1; //x = x >> 1;
 * 
 * 31>     }
 * 
 * 32<     }
 * 
 * 32>     printf("\n");
 * 
 * 33<     printf("\n");
 * 
 * 33>}
 * 
 * 34<}
 * 
 * 34>//output:
 * 
 * 35<unsigned countBits(unsigned int number){
 * 
 * 35>/*
 * 
 * 36<      return (int)log2(number)+1;
 * 
 * 36>quanglvn@quanglvn:~/thuviec/123$ gcc 2-9.c -o 2-9
 * 
 * 37<}
 * 
 * 37>quanglvn@quanglvn:~/thuviec/123$ ./2-9
 * 
 * 38<//output
 * 
 * 38>10011011110001111
 * 
 * 39</*
 * 
 * 39>number of '1' bit: 11
 * 
 * 40<quanglvn@quanglvn:~/thuviec/123$ gcc 2-8.c -o 2-8 -lm
 * 
 * 40>*
 * quanglvn@quanglvn:~/1$
 */