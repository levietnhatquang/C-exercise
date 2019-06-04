/*
 * Exercise 1-4. Write a program to print the corresponding Celsius to Fahrenheit
 * table.
 */


#include <stdio.h>
/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300; floating-point version 
 */
int main(){
	float fahr, Celsius;
	int lower, upper, step;

	lower = -200; /* lower limit of temperature table */
	upper = 300; /* upper limit */
	step = 50; /* step size */

	printf("Celsius temperatures and their Fahrenheit equivalents:\n");
	Celsius = lower;
	while (Celsius <= upper) {
		fahr = Celsius / (5.0/9.0) + 32.0;
		printf("%6.0f %3.0f \n", Celsius, fahr);
		Celsius = Celsius + step;
	}
	return 0;
}

/* output
 * 
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-4.c -o 1-4
 * quanglvn@quanglvn:~/thuviec/123$ ./1-4
 * Celsius temperatures and their Fahrenheit equivalents:
 *   -200 -328 
 *   -150 -238 
 *   -100 -148 
 *    -50 -58 
 *      0  32 
 *     50 122 
 *    100 212 
 *    150 302 
 *    200 392 
 *    250 482 
 *    300 572 
 */