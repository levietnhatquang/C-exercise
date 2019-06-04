/*
 * Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to
 * use a function for conversion.
 */
#include <stdio.h>
/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300; floating-point version 
 */
float FtoC(float f){
	return (5.0/9.0) * (f-32.0);
}

int main(){
	float fahr, Celsius;
	int lower, upper, step;

	lower =0; /* lower limit of temperature table */
	upper = 300; /* upper limit */
	step =20; /* step size */

	printf("Fahrenheit temperatures and their centigrade or Celsius equivalents:\n");
	fahr = lower;
	while (fahr <= upper) {
		Celsius = FtoC(fahr);
		printf("%3.0f %6.1f \n", fahr, Celsius);
		fahr = fahr + step;
	}
	return 0;
}
/*
 * output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-15.c -o 1-15
 * quanglvn@quanglvn:~/thuviec/123$ ./1-15
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