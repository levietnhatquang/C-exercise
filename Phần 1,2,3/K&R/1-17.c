/*
 * Exercise 1-17. Write a program to print all input lines that are longer than 80
 * characters.
 */
#include<stdio.h>
#define MAX 100 //max # of line can save
#define MAXLINE 1000 //mac # characters/line
#define LIM 80 //number of limit characters

int Count(char ch[]);
void Save(char from[], char to[]);

int main(){
	char Saved_Array[MAX][MAXLINE];
	char Tmp_Line[MAXLINE];
	int len;
	int i = 0;
	for(int i = 0; i<MAX; i++)
		Saved_Array[i][0] = '\0';

	while ((len = Count(Tmp_Line)) > 0){
		//printf("%d \n", len);
		if (len > LIM){
			Save(Tmp_Line, Saved_Array[i]);
			i++;
		}
	}
	for(int i = 0; i<MAX; i++){
		if (Saved_Array[i][0] != '\0'){
			for(int j=0; j<MAXLINE; j++)
				printf("%c", Saved_Array[i][j]);
			printf("\n");
		}
	}
}

int Count(char ch[]){ //count number of character
	int c, l;
	l = 0;
	int i;
	for (i = 0; i<MAXLINE-1 && (c=getchar())!=EOF && c!='\n'; i++){
		ch[i] = c;
		l++;
	}
	ch[i] = '\0';
	return l;
}

void Save(char from[], char to[]){ //save >80-character lines
	int i = 0;
	while (from[i] != '\0'){
		to[i] = from[i];
		i++;
	}
}

/* Output
 *
 * Quangs-MacBook:123 quanglvn$ gcc 1-17.c -o 1-17
 * Quangs-MacBook:123 quanglvn$ ./1-17
 * 555555555555555555
 * 1233333333333333333333333333333333333333333333333333333333333333333333333333333333333333
 * 8123333333333333333333333333
 * 123
 * 13
 * 1
 * 00000000000000000000  0000000000  0000000000  0000000000  0000000000  0000000000  0000000000  0000000000  0000000000  
 * 
 * 1233333333333333333333333333333333333333333333333333333333333333333333333333333333333333
 * 00000000000000000000  0000000000  0000000000  0000000000  0000000000  0000000000  0000000000  0000000000  0000000000  
 */