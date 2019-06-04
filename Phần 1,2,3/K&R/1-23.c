/*
 * Exercise 1-23. Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C com-
 * comments do not nest.
 */
#include<stdio.h>
#define MAXCHAR 1000
#define MAXLINE 1000

int main(){
	int c, state, i; //state: 1 - inside quote, 2 - outside quote
	char Buffer[MAXCHAR];
	i = 0;
	state = 0;
	while((c = getchar()) != EOF){
		Buffer[i++] = c;
		if (c == '"'){
			if (state)
				state = 0;
			else
				state = 1;
		}
		if(state == 0 && c == '/'){
			i = i - 1;
		}
	}
	Buffer[i] = '\0';
	i = 0;
	while(Buffer[i] != '\0'){
		printf("%c", Buffer[i]);
		i++;
	}
	return 0;
}
/* 
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-23.c -o 1-23
 * quanglvn@quanglvn:~/thuviec/123$ ./1-23
 *
 * Exercise 1-23. Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C com-
 * comments do not nest.
 *
 * #include<stdio.h>
 * #define MAXCHAR 1000
 * #define MAXLINE 1000
 * 
 * int main(){
 * 	int c, state, i; //state: 1 - inside quote, 2 - outside quote
 * 	char Buffer[MAXCHAR];
 * 	i = 0;
 * 	state = 0;
 * 	while((c = getchar()) != EOF){
 * 		Buffer[i++] = c;
 * 		if (c == '"'){
 * 			if (state)
 * 				state = 0;
 * 			else
 * 				state = 1;
 * 		}
 * 		if(state == 0 && c == '/'){
 * 			i = i - 1;
 * 		}
 * 	}
 * 	Buffer[i] = '\0';
 * 	i = 0;
 * 	while(Buffer[i] != '\0'){
 * 		printf("%c", Buffer[i]);
 * 		i++;
 * 	}
 * 	return 0;
 * }
 *
 * Exercise 1-23. Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C com-
 * comments do not nest.
 *
 * #include<stdio.h>
 * #define MAXCHAR 1000
 * #define MAXLINE 1000
 * 
 * int main(){
 * 	int c, state, i; state: 1 - inside quote, 2 - outside quote
 * 	char Buffer[MAXCHAR];
 * 	i = 0;
 * 	state = 0;
 * 	while((c = getchar()) != EOF){
 * 		Buffer[i++] = c;
 * 		if (c == '"'){
 * 			if (state)
 * 				state = 0;
 * 			else
 * 				state = 1;
 * 		}
 * 		if(state == 0 && c == '/'){
 * 			i = i - 1;
 * 		}
 * 	}
 * 	Buffer[i] = '\0';
 * 	i = 0;
 * 	while(Buffer[i] != '\0'){
 * 		printf("%c", Buffer[i]);
 * 		i++;
 * 	}
 * 	return 0;
 * }
 */