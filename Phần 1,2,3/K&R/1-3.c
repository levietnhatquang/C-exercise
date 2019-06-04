/*
 * Exercise 1-3. Modify the temperature conversion program to print a heading
 * above the table.
 *
 * NOTE
 * char character—a single byte
 * short short integer
 * long long integer
 * double double-precision floating point
 * 
 * %d print as decimal integer
 * %6d print as decimal integer, at least 6 characters wide
 * %f print as floating point
 * %6f print as floating point, at least 6 characters wide
 * %. 2f print as floating point, 2 characters after decimal point
 * %6. 2f print as floating point, at least 6 wide and 2 after decimal point
 */

#include <stdio.h>
/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300; floating-point version
 */
int main(){
	float fahr, Celsius;
	int lower, upper, step;

	lower = 0; /* lower limit of temperature table */
	upper = 300; /* upper limit */
	step = 20; /* step size */

	printf("Fahrenheit temperatures and their centigrade or Celsius equivalents:\n");
	fahr = lower;
	while (fahr <= upper) {
		Celsius = (5.0/9.0) * (fahr-32.0);
		printf("%3.0f %6.1f \n", fahr, Celsius);
		fahr = fahr + step;
	}
	return 0;
}

/* output
 * 
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-3.c -o 1-3
 * quanglvn@quanglvn:~/thuviec/123$ ./1-3 
 * Fahrenheit temperatures and their centigrade or Celsius equivalents:
 *   0  -17.8 
 *  20   -6.7 
 *  40    4.4 
 *  60   15.6 
 *  80   26.7 
 * 100   37.8 
 * 120   48.9 
 * 140   60.0 
 * 160   71.1 
 * 180   82.2 
 * 200   93.3 
 * 220  104.4 
 * 240  115.6 
 * 260  126.7 
 * 280  137.8 
 * 300  148.9 
 */