/*
 * Exercise 2-3. Write the function htoi (s), which converts a string of
 * hexadecimal digits (including an optional Ox or OX) into its equivalent integer value.
 * The allowable digits are 0 through 9, a through f, and A through F.
 *
 * NOTE
 *
 * ERROR even included math.h: 
 * /tmp/ccY7MZnI.o: In function `htoi':
 * 2-3.c:(.text+0x155): undefined reference to `pow'
 * 2-3.c:(.text+0x1b4): undefined reference to `pow'
 * 2-3.c:(.text+0x213): undefined reference to `pow'
 * 2-3.c:(.text+0x272): undefined reference to `pow'
 * 2-3.c:(.text+0x2d1): undefined reference to `pow'
 * /tmp/ccY7MZnI.o:2-3.c:(.text+0x330): more undefined references to `pow' follow
 * collect2: error: ld returned 1 exit status
 * 
 * Fix:
 * gcc 2-3.c -o 2-3 -lm
 * "The error you are seeing: error: ld returned 1 exit status is from the linker ld
 * (part of gcc that combines the object files) because it is unable to find where the
 * function pow is defined.
 * Including math.h brings in the declaration of the various functions and not their 
 * definition. The def is present in the math library libm.a. You need to link your 
 * program with this library so that the calls to functions like pow() are resolved."
 */


#include<stdio.h>
#include<math.h>
#define MAXCHAR 100

int htoi(char *Buffer, int start_idx, int stop_idx);

int main(){
	char Buffer[MAXCHAR];
	int c, i, state, start_idx, stop_idx, valid;
	state = 0; //1: met '0', 2: met '0x',
	i = 0;
	valid = 0;
	while((c = getchar()) != EOF){
		Buffer[i++] = c;
		if(state == 0){
			if(c == '0'){
				//putchar('*');
				state = 1;
				continue;
			}
		}
		if(state == 1){
			//printf("-%d-", i);
			//printf("'%d'", c);
			if (c == 'x' || c == 'X'){
				state = 2;
				//putchar('~');
				start_idx = i; //hexadecimal start after 'x' of 'X'
				continue;
			}
			else{
				state = 0;
			}
		}
		if(state == 2){
			if((48 <= c && c <= 57) || (65 <= c && c <= 90) || (97 <= c && c <= 122)){
				stop_idx = i - 1;
				valid = 1;
			}
			else {
				state = 0;
			}
		}
	}
	if (valid)
		printf("In decimal: %d", htoi(Buffer, start_idx, stop_idx));
	else
		printf("No hexadecimal string found!");
	return 0;
}
int htoi(char *Buffer, int start_idx, int stop_idx){
	int power_idx = 0; //power # for 16-base
	int decimal = 0;
	for(int i = stop_idx; i >= start_idx; i--){
		//putchar(Buffer[i]);
		if(Buffer[i] == 'A' || Buffer[i] == 'a')
			decimal += 10 * pow(16, power_idx++);
		else if(Buffer[i] == 'B' || Buffer[i] == 'b')
			decimal += 11 * pow(16, power_idx++);
		else if(Buffer[i] == 'C' || Buffer[i] == 'c')
			decimal += 12 * pow(16, power_idx++);
		else if(Buffer[i] == 'D' || Buffer[i] == 'd')
			decimal += 13 * pow(16, power_idx++);
		else if(Buffer[i] == 'E' || Buffer[i] == 'e')
			decimal += 14 * pow(16, power_idx++);
		else if(Buffer[i] == 'F' || Buffer[i] == 'f')
			decimal += 15 * pow(16, power_idx++);
		else 
			decimal += (Buffer[i] - '0') * pow(16, power_idx++);
		//printf("-%d-", decimal);
	}
	return decimal;
}
/* output
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 2-3.c -o 2-3 -lm
 * quanglvn@quanglvn:~/thuviec/123$ ./2-3
 * jh*(&%jkhkje 0xA1b 8kiUT(478
 * In decimal: 2587
 */