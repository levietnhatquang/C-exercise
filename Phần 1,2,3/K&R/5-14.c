/*
 * Exercise 5-14. Modify the sort program to handle a -r flag, which indicates
 * sorting in reverse (decreasing) order. Be sure that -r works with -n.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000 /* max # lines to be sorted */

char *lineptr[MAXLINES]; /* 5000 pointers to char */
int mode = 1; /* 1 if flag -r is on => reverse order*/ 

int Getline(char s[], int lim);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void Qsort(void *lineptr[], int left, int right, int (*comp)(char *, char *));
int numcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines; /* number of input lines read */
	int numeric = 0; /* 1 if numeric sort */
	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;
	if (argc > 2 && strcmp(argv[2], "-r") == 0)
		mode = -1;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		Qsort((void **) lineptr, 0, nlines-1,
		(int (*)(char*,char*))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("input too big to sort\n");
		return 1;
	}
}

/* get 1 line into s[] */
int Getline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    s[i] = c;
  if (c == '\n') {
    s[i++] = c;
  }
  s[i] = '\0';
  return i;
}

/* Get many line into lineptr, return number of line got*/
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLINES];

  nlines = 0;
  while ((len = Getline(line, MAXLINES)) > 0)
    if (nlines >= maxlines || (p = malloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0';  /* delete the newline */
      strcpy(p, line); // store line from Getline() to created line
      lineptr[nlines++] = p; //point each pointer to created line
    }
  return nlines;
}

/* print all got lines */
void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}


/* Qsort: sort v[left]...v[right] into increasing order */
void Qsort(void *v[], int left, int right, int (*comp)(char *, char *))
	{
	int i, last;
	void swap(void *v[], int, int);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left])*mode < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	Qsort(v, left, last-1, comp);
	Qsort(v, last+1, right, comp);
}

int numcmp(char *s1, char *s2){
	double v1, v2;
	v1 = atof (s1) ;
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
/* output:
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-14.c -o 5-14
 * 5-14.c: In function ‘main’:
 * 5-14.c:31:43: warning: pointer type mismatch in conditional expression
 *    (int (*)(char*,char*))(numeric ? numcmp : strcmp));
 *                                            ^
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-14 -n
 * 1  
 * 3
 * 2
 * 1
 * 2
 * 3
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-14 -n -r
 * 1 
 * 3
 * 2
 * 3
 * 2
 * 1
 * 
 * NOTE: warning due to int strcmp(constant char *s1, constant char *s2)
 */