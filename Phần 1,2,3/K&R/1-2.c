/*
 * Exercise 1-2. Experiment to find out what happens when printf's argument
 * string contains \c, where c is some character not listed above.
 */
#include <stdio.h>

main(){
	printf("hello, \ccc ");
	printf("world");
	printf("\n");
}

/* output:
 *
 * quanglvn@quanglvn:~/thuviec/123$ gcc 1-2.c -o 1-2
 * 1-2.c:7:1: warning: return type defaults to ‘int’ [-Wimplicit-int]
 *  main()
 *  ^
 * 1-2.c: In function ‘main’:
 * 1-2.c:9:9: warning: unknown escape sequence: '\c'
 *   printf("hello, \ccc ");
 *          ^
 * quanglvn@quanglvn:~/thuviec/123$ ./1-2
 * hello, ccc world
 */

/* comment:
 *
 * key word: "C excape sequence"
 * C available escape sequence:
 * \a    Alarm or Beep   
 * \b    Backspace
 * \f    Form Feed
 * \n    New Line
 * \r    Carriage Return
 * \t    Tab (Horizontal)
 * \v    Vertical Tab
 * \\    Backslash
 * \'    Single Quote
 * \"    Double Quote
 * \?    Question Mark
 * \ooo  octal number
 * \xhh  hexadecimal number
 * \0    Null
 */