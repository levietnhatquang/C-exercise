/*
 * Exercise 2-2. Write a loop equivalent to the for loop above without using &&
 * or ! !.
 */
#include <stdio.h>
#define LIM 1000

int main(void) {
    int c, i;
    for (i = 0; ((i < LIM - 1) + ((c = getchar()) != EOF) + (c != '\n')) == 3; ++i) {
        putchar(c);
    }
}