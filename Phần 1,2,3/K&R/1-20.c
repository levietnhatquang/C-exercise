/*
 * Exercise 1-20. Write a program detab that replaces tabs in the input with the
 * proper number of blanks to space to the next tab stop. Assume a fixed set of
 * tab stops, say every n columns. Should n be a variable or a symbolic parame-
 * parameter? => symbolic parameter
 */
#include<stdio.h>
#define N 8 //tab stops at every 8 blanks
#define MAXCHAR 1000

int main(){
	int c, i, j;
	char Buffer[MAXCHAR];
	i = 0;
	j = 0;
	while((c = getchar()) != EOF){
		if(c == '\t'){
			Buffer[j] = N - (i % N) + '0';
			//printf("'%d %d %d'",i,j,N - (i % N));
			if (Buffer[j] == 0)
				Buffer[j] = 8 + '0';
			i = i + N - (i % N);
			j++;
		}
		else{
			Buffer[j++] = c;
			i++;
		}
	}
	Buffer[j] = '\0';
	for(int i = 0; i < MAXCHAR; i++)
		if (Buffer[i] == '\0')
			break;
		else
			printf("%c", Buffer[i]);
	return 0;
}
/* output:
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-20.c -o 1-20
 * quanglvn@quanglvn:~/thuviec/123$ ./1-20
 * 1	22	333	|
 * 4444	88888888	|
 * 172263335|
 * 44442888888888|
 */