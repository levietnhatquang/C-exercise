/*
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the
 * same tab stops as for detab. When either a tab or a single blank would suffice
 * to reach a tab stop, which should be given preference?
 */
#include<stdio.h>
#define N 8 //tab stops at every 8 blanks
#define MAXCHAR 1000

int distance_to_next_tab(int idx);

int main(){
	int c, i, flag, counter;
	char Buffer[MAXCHAR];
	i = 0;
	flag = 0;
	counter = 0;
	while((c = getchar()) != EOF){
		if(c == ' '){
			if(flag == 0)
				flag = 1;
			counter++;
		}
		else{
			int d = distance_to_next_tab(i);
			if(counter > d){
				counter = counter - d;
				Buffer[i++] = '\t';
			}
			int t = counter/N;
			int b = counter%N;
			//printf("'%d %d'", t, b);
			while(t-- > 0){
				Buffer[i++] = '\t';
			}
			while(b-- > 0){
				Buffer[i++] = ' ';
			}
			counter = 0;
			flag = 0;
			Buffer[i++] = c;
		}
	}
	Buffer[i] = '\0';
	for(int i = 0; i < MAXCHAR; i++)
		if (Buffer[i] == '\0')
			break;
		else
			printf("%c", Buffer[i]);
	return 0;
}

int distance_to_next_tab(int idx){
	int d;
	d = N - (idx % N);
	//printf("-%d-",d);
	if (d == 0)
		d = 8;
	return d;
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-21.c -o 1-21
 * quanglvn@quanglvn:~/thuviec/123$ ./1-21
 * 1    2
 * 1            2
 * 1                     2
 * 1    2
 * 1			 2
 * 1		     		  2
 */