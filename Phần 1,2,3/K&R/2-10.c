/*
 * Exercise 2-10. Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expression instead of if-else.
 */
#include<stdio.h>

void Lower(char *String);

int main(){
	char *String = "JK89$rnu&*1DyhAdf";
	int i = 0;
	while(*(String + i) != '\0'){
		printf("%c", *(String + i));
		i++;
	}
	printf("\n");
	Lower(String);
}
void Lower(char *String){
	int i = 0;
	int tmp;
	while(*(String + i) != '\0'){
		tmp = (65 <= *(String + i) && *(String + i) <= 90) ? *(String + i) + 32 : *(String + i);
		printf("%c", tmp);
		i++;
	}
	printf("\n");
}
/*output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 2-10.c -o 2-10
 * quanglvn@quanglvn:~/thuviec/123$ ./2-10
 * JK89$rnu&*1DyhAdf
 * jk89$rnu&*1dyhadf
 */