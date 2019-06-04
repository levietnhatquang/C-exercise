/*
 * Exercise 2-4. Write an alternate version of squeeze(s1 ,s2) that deletes
 * each character in s1 that matches any character in the string s2.
 */
#include<stdio.h>

void squeeze(char *s1, char *s2);

int main(){
	char s1[] = "alskdj";
	char s2[] = "asdiof";
	squeeze(s1, s2);
	int i = 0;
	while( *(s1 + i) != '\0'){
		printf("%c", *(s1 + i));
		i++;
	}
	return 0;
}
void squeeze(char *s1, char *s2){
	int counter = 0;
	int flag = 0;
	for(int i = 0; *(s1 + i) != '\0'; i++){
		for(int j = 0; *(s2 + j) != '\0'; j++){
			if (*(s1 + i) == (*s2 + j)){
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			*(s1+counter) = *(s1 + i);
			counter++;
		}
		flag = 0;
	}
	*(s1 + counter) = '\0';
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 2-4.c -o 2-4
 * quanglvn@quanglvn:~/thuviec/123$ ./2-4
 * lskj
 */