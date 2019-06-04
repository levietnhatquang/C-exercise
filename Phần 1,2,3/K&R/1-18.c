/*
 * Exercise 1-18: write a program to remove trailing blanks from each line
 * of input and to delete entirely blank line
 */
#include<stdio.h>
#define MAXLINE 10
#define MAXCHAR 20

void Save_line(char *from, char *to);

int main(){
	char Save_Array[MAXLINE][MAXCHAR];
	char tmp[MAXCHAR];
	int c, flag_t, flag_b, flag_n, counter_ch, counter_l;
	flag_t = 0; //1: previous is tab
	flag_b = 0; //1: previous is backspace
	flag_n = 0; //1: previous is newline
	counter_ch = 0;
	counter_l = 0;

	for(int i = 0; i<MAXLINE; i++)
		Save_Array[i][0] = '\0';

	while((c = getchar()) != EOF){
		if (c == '\t'){
			if (flag_t == 0){
				flag_t = 1;
				flag_b = 0;
				flag_n = 0;
			}
			else
				continue;
		}
		else if (c == ' '){
			if (flag_b == 0){
				flag_b = 1;
				flag_n = 0;
				flag_t = 0;
			}
			else
				continue;
		}
		else if (c == '\n'){
			if (flag_n == 0){
				flag_n = 1;
				flag_b = 0;
				flag_t = 0;
				tmp[counter_ch++] = c;
				Save_line(tmp, Save_Array[counter_l]);
				counter_l++;
				counter_ch = 0;
				continue;
			}
			else
				continue;
		}
		else{
			flag_t = 0;
			flag_b = 0;
			flag_n = 0;
		}
		tmp[counter_ch++] = c;
	}
	for(int i = 0; i<MAXLINE; i++){
		if (Save_Array[i][0] == '\0')
			continue;
		for(int j=0; j<MAXCHAR; j++){
			printf("%c", Save_Array[i][j]);
			if (Save_Array[i][j] == '\n')
				break;
		}
	}

	return 0;
}

void Save_line(char *from, char *to){
	int i = 0;
	while(from[i] != '\n'){
		//printf("%c",from[i]);
		to[i] = from[i];
		i++;
	}
	to[i] = '\n';
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-18.c -o 1-18
 * quanglvn@quanglvn:~/thuviec/123$ ./1-18
 * 1  2		3
 * 
 * 
 * 4
 * 56
 * 1 2	3
 * 4
 * 56
 */