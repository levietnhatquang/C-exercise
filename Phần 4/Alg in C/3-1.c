/*
 * Find the largest and smallest numbers that you can represent with
 * types int, long int, short int, float, and double in your programming
 * environment.
 */
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) 
{
  printf("int min: \t%d, \tint max: \t%d\n", INT_MIN, INT_MAX);
  printf("long min: \t%ld, \tlong max: \t%ld\n", LONG_MIN, LONG_MAX);
  printf("short min: \t%d, \tshort max: \t%d\n", SHRT_MIN, SHRT_MAX);
  printf("float min: \t%f, \tfloat max: \t%f\n", FLT_MIN, FLT_MAX);
  printf("double min: \t%lf, \tdouble max: \t%lf\n", DBL_MIN, DBL_MAX);
  return 0;
}