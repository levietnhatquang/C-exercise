/*
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 */
#include<stdio.h>
#define N 8 //tab stops at every 8 blanks
#define MAXCHAR 1000
#define MAXLINE 1000
#define COL_LIMIT 100

int main(){
	int c, i, j, tmp, counter; //tmp: temporary last line
	char Buffer[MAXCHAR]; //store original input
	int Last[MAXLINE]; //store position of last character
	for(int i = 0; i < MAXLINE; i++){
		Last[i] = 0;
	}
	i = 0;
	j = 0;
	counter = 0;
	while((c = getchar()) != EOF){
			Buffer[i] = c;
			if (c > 32 && counter < COL_LIMIT){
				counter++;
				tmp = i;
			}
			if (c == '\n' || counter >= COL_LIMIT){
				counter = 0;
				Last[j++] = tmp;
				//printf(" %d ", tmp);
			}
			i++;
	}
	Buffer[i] = '\0';
	i = 0;
	j = 0;
	while(Buffer[i] != '\0'){
		if(i == Last[j]){
			printf("\n");
			j++;
		}
		printf("%c", Buffer[i]);
		i++;
	}
	return 0;
}
/*output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-22.c -o 1-22
 * quanglvn@quanglvn:~/thuviec/123$ ./1-22
 * ASCII stands for American Standard Code for Information Interchange. Computers can only understand numbers, so an ASCII code is the numerical representation of a character such as 'a' or '@' or an action of some sort. ASCII was developed a long time ago and now the non-printing characters are rarely used for their original purpose. Below is the ASCII character table and this includes descriptions of the first 32 non-printing characters. ASCII was actually designed for use with teletypes and so the descriptions are somewhat obscure. If someone says they want your CV however in ASCII format, all this means is they want 'plain' text with no formatting such as tabs, bold or underscoring - the raw format that any computer can understand. This is usually so they can easily import the file into their own applications without issues. Notepad.exe creates ASCII text, or in MS Word you can save a file as 'text only'
 * ASCII stands for American Standard Code for Information Interchange. Computers can only understand numbers, so an A
 * SCII code is the numerical representation of a character such as 'a' or '@' or an action of some sort. ASCII was developed 
 * a long time ago and now the non-printing characters are rarely used for their original purpose. Below is the ASCII chara
 * cter table and this includes descriptions of the first 32 non-printing characters. ASCII was actually designed for us
 * e with teletypes and so the descriptions are somewhat obscure. If someone says they want your CV however in ASCII format
 * , all this means is they want 'plain' text with no formatting such as tabs, bold or underscoring - the raw format that any c
 * omputer can understand. This is usually so they can easily import the file into their own applications without issues. 
 * Notepad.exe creates ASCII text, or in MS Word you can save a file as 'text only
 */