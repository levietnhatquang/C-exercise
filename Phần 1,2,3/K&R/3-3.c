/*
 * Exercise 3-3. Write a function expand(s1 ,s2) that expands shorthand nota-
 * notations like a-z in the string s1 into the equivalent complete list abc...xyz in
 * s2. Allow for letters of either case and digits, and be prepared to handle cases
 * like a-b-c and a-zO-9 and -a-z. Arrange that a leading or trailing - is
 * taken literally.
 */
#include<stdio.h>
#define MAXCHAR 1000

int expand(char *s1, char *s2);

int main(){
	char s1[8][10] = {"B-Y", "a-z-", "z-a-", "-1-6-", "a-ee-a", "a-R-L", "1-9-1", "5-5", NULL};
	char s2[MAXCHAR];
	int i = 0;
	while(i<9){
		if(expand(*(s1 + i), s2)){
	        printf("Unexpanded string: %s\n", s1[i]);
	        printf("Expanded string: %s\n", s2);
	    }
	    else{
	    	printf("Unexpanded string: %s is invalid\n", s1[i]);
	    }
	    i++;
	}
	return 0;
}

int expand(char *s1, char *s2){
	static char upper_alph[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static char lower_alph[27] = "abcdefghijklmnopqrstuvwxyz";
    static char digits[11]     = "0123456789";
    int	i = 0;

	if(65 <= s1[i] && s1[i] <= 90)
		if(s1[i+1] == '-')
			if(s1[i+2] <= 90 && s1[i+2] > s1[i])
				 if(s1[i+3] == '\0'){
				 	int k = 0;
				 	for(int j = s1[i]; j <= s1[i+2]; j++){
				 		*(s2 + k++) = j;
				 	}
				 	return 1;
				 }

	if(97 <= s1[i] && s1[i] <= 122)
		if(s1[i+1] == '-')
			if(s1[i+2] <= 97 && s1[i+2] > s1[i])
				 if(s1[i+3] == '\0'){
				 	int k = 0;
				 	for(int j = s1[i]; j <= s1[i+2]; j++){
				 		*(s2 + k++) = j;
				 	}
				 	return 1;
				 }

	if(48 <= s1[i] && s1[i] <= 57)
		if(s1[i+1] == '-')
			if(s1[i+2] <= 97 && s1[i+2] > s1[i])
				 if(s1[i+3] == '\0'){
				 	int k = 0;
				 	for(int j = s1[i]; j <= s1[i+2]; j++){
				 		*(s2 + k++) = j;
				 	}
				 	return 1;
				 }

	return 0;
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 3-3.c -o 3-3 -w
 * quanglvn@quanglvn:~/thuviec/123$ ./3-3
 * Unexpanded string: B-Y
 * Expanded string: BCDEFGHIJKLMNOPQRSTUVWXY
 * Unexpanded string: a-z- is invalid
 * Unexpanded string: z-a- is invalid
 * Unexpanded string: -1-6- is invalid
 * Unexpanded string: a-ee-a is invalid
 * Unexpanded string: a-R-L is invalid
 * Unexpanded string: 1-9-1 is invalid
 * Unexpanded string: 5-5 is invalid
 * Unexpanded string:  is invalid
 */