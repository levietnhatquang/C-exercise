/*
 * Exercise 4-1. Write the function strrindex(s, t), which returns the position
 * of the rightmost occurrence of t in s, or -1 if there is none.
 */
#include<stdio.h>

int strrindex(char *s, char t);

int main(){
	char s[] = "qweituwpeq";
	char t = 'e';
	int idx = strrindex(s,t);
	if (idx != -1)
		printf("Right most '%c' is at index %d\n", t, idx);
	else
		printf("Letter not found!\n");
	return 0;
}

int strrindex(char *s, char t){
	int i = 0;
	int tmp_idx = 0;
	while(*(s + i) != '\0'){
		if(*(s + i) == t){
			tmp_idx = i;
		}
		i++;
	}
	if(tmp_idx != 0)
		return tmp_idx;
	else
		return -1;
}
/*
 * output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 4-1.c -o 4-1
 * quanglvn@quanglvn:~/thuviec/123$ ./4-1
 * Right most 'e' is at index 8
 */