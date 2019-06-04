/*
 * Exercise 5-16. Add the -d ("directory order") option, which makes comparis-
 * comparisons only on letters, numbers and blanks. Make sure it works in conjunction
 * with -f.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXLINES 5000 /* max # lines to be sorted */

char *lineptr[MAXLINES]; /* 5000 pointers to char */
int mode = 1; /* -1 if flag -r is on => reverse order*/ 
int fold = 0; /* 1 if flag -r is on => reverse order*/
int dir = 0; 

int Getline(char s[], int lim);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void Qsort(char *lineptr[], int left, int right, int (*comp)(const char *,const char *));
int numcmp(const char *, const char *);
int Strcmp (const char *p1, const char *p2);

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines; /* number of input lines read */
	int numeric = 0; /* 1 if numeric sort */
	for (int i = 1; i < argc; i++){
		if (strcmp(argv[i], "-n") == 0)
			numeric = 1;
		else if (strcmp(argv[i], "-r") == 0)
			mode = -1;
		else if (strcmp(argv[i], "-f") == 0)
			fold = 1;
		else if (strcmp(argv[i], "-f") == 0)
			fold = 1;
		else if (strcmp(argv[i], "-d") == 0)
			dir = 1;
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		Qsort((char **) lineptr, 0, nlines-1,
		(int (*)(const char*, const char*))(numeric ? numcmp : Strcmp));
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
void Qsort(char *v[], int left, int right, int (*comp)(const char *, const char *))
	{
	int i, last;
	void swap(char *v[], int, int);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++){
		if (dir && ((65 <= *v[i] && *v[i] <= 90) || (97 <= *v[i] && *v[i] <= 122) || *v[i] == 9
			|| (65 <= *v[left] && *v[left] <= 90) || (97 <= *v[left] && *v[left] <= 122) || *v[left] == 9))
			
		if ((*comp)(v[i], v[left])*mode < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	Qsort(v, left, last-1, comp);
	Qsort(v, last+1, right, comp);
}

int numcmp(const char *s1, const char *s2){
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

void swap(char *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int Strcmp (const char *p1, const char *p2)
{
	const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;
	do{
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (fold && c1 >= 97 && c1 <= 122)
			c1 -= ('a' - 'A');
		if (fold && c2 >= 97 && c2 <= 122)
			c2 -= ('a' - 'A');
			return c1 - c2;
	}while (c1 == c2);
	return c1 - c2;
}
/*output
 *
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-16.c -o 5-16
 * quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-16 -d
 * a
 * $
 * b
 * ^
 * c
 *  
 *  
 * e
 * .
 * d
 * ^
 * .
 * $
 *  
 *  
 * a
 * b
 * c
 * d
 * e
 */