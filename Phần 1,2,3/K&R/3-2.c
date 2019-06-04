/*
 * Exercise 3-2. Write a function escape (s,t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies the
 * string t to s. Use a switch. Write a function for the other direction as well,
 * converting escape sequences into the real characters.
 */
#include<stdio.h>
#define MAXCHAR 1000

int main(){
	int c;
	char Buffer[MAXCHAR];
	int i = 0;
	while((c = getchar()) != EOF){
		switch(c){
			case ' ': {
				Buffer[i++] = '\\';
				Buffer[i++] = 'b';
				break;
			}
			case '\n': {
				Buffer[i++] = '\\';
				Buffer[i++] = 'n';
				break;
			}
			case '\t': {
				Buffer[i++] = '\\';
				Buffer[i++] = 't';
				break;
			}
			default: Buffer[i++] = c;
		}
	}
	Buffer[i++] = '\0';
	i = 0;
	while(Buffer[i] != '\0'){
		putchar(Buffer[i]);
		i++;
	}

	return 0;
}
/*output:
 *
 * quanglvn@quanglvn:~/thuviec/123$ ./3-2
 * -tab:	-newline:
 * -spacex5:     
 * -tab:\t-newline:\n-spacex5:\b\b\b\b\bquanglvn@quanglvn:~/thuviec/123$ 
 */