/*
 * Exercise 1-5. Modify the temperature conversion program to print the table in
 * reverse order, that is, from 300 degrees to 0.
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

	printf("Celsius temperatures and their Fahrenheit equivalents in reverse order:\n");
	Celsius = upper;
	while (Celsius >= lower) {
		fahr = Celsius / (5.0/9.0) + 32.0;
		printf("%6.0f %3.0f \n", Celsius, fahr);
		Celsius = Celsius - step;
	}
	return 0;
}
/*
 * output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-5.c -o 1-5
 * quanglvn@quanglvn:~/thuviec/123$ ./1-5
 * Celsius temperatures and their Fahrenheit equivalents in reverse order:
 *    300 572 
 *    250 482 
 *    200 392 
 *    150 302 
 *   100 212 
 *     50 122 
 *      0  32 
 *    -50 -58 
 *   -100 -148 
 *   -150 -238 
 *   -200 -328 
 */
