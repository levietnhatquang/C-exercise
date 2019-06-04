/*
 * Exercise 6-2. Write a program that reads a C program and prints in
 * alphabetical order each group of variable names that are identical in the first 6 
 * characters, but different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getch.h"

#define MAXWORD 100
#define key_num 40 /* number of C key word */

int n = 6;
struct tnode{
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *); 
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *Strdup(char *);
int my_strcmp(char *s1, char *s2);
int is_var(char *s);
int is_key_word(char *s);
int is_string(char *s);
int is_comment(char *s);

int main(int argc, char *argv[]){
	struct tnode *root;
	char word[MAXWORD];
	root = NULL;
	int state = 0; /* precious is variable decle */

	if(argc > 1 && atoi(*(argv + 1)) != 0){
		n = atoi(*(argv + 1));
		printf("Using %d idential characters to compare\n", n);
	} else{
		printf("Using default %d idential characters to compare\n", n);
	}

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && is_var(word))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL) { /* a new word has arrived */
		p = talloc(); /* make a new node */
		p->word = Strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++; /* repeated word */
	else if (cond < 0) /* less than into left subtree */
		p->left = addtree(p->left, w);
	else /* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: in-order print of tree p */
char *tmp_tnode = NULL;
int gr = 0;
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		if (!my_strcmp(tmp_tnode, p->word))
			printf("Group %d:\n",gr++);
		printf("%4d %s\n", p->count, p->word);
		tmp_tnode = p->word;
		treeprint(p->right);
	}
}

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	char x = (char)c;
	is_string(&x); /* record string state */
	is_comment(&x); /* record comment state */
	if (!isalpha(c)){
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!(isalnum(*w = getch()) || (*w == '_'))){
			ungetch(*w);
			break;
	}
	*w = '\0';
	return word[0];
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *Strdup(char *s) /* make a duplicate of s */
{
	char *p;
	p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* check if has the same n first character, return boolean */
int my_strcmp(char *s1, char *s2)
{
	if(s1 != NULL){
		char *p1 = s1;
		char *p2 = s2;
		char c1, c2;
		int counter = n;
		do{
			c1 = *p1++;
			c2 = *p2++;
			if (counter-- == 0)
				return 1;
			if (c1 == '\0')
				return 0;
		}while (c1 == c2);
	}
	return 0;
}

int is_key_word(char *s)
{
	static char *List[key_num] = {"auto",	"break",	"case",	"char",
				"const",	"continue",	"default",	"do",
				"double",	"else",	"enum",	"extern",
				"float",	"for",	"goto",	"if",
				"int",	"long",	"register",	"return",
				"short",	"signed",	"sizeof",	"static",
				"struct",	"switch",	"typedef",	"union",
				"unsigned",	"void",	"volatile",	"while",
				"EOF", "stdio", "printf", "stdlib",
				"strmp", "struct", "do", "void"};
	for (int i = 0; i < key_num; i++){
		if (strcmp(List[i], s) == 0)
			return 1;
	}
	return 0;
}

int state_s = 0; /* tmp = 1: met " */
int is_string(char *s)
{
	if(*s == '"')
		state_s ^= 1;
	return state_s;
}

int tmp_c = 0;
int state_c = 0;
int is_comment(char *s)
{
	int c = *s;
	if (c == '/')
		tmp_c = 1;
	if (c == '*' && tmp_c == 1){
		state_c = 1;
		tmp_c = 2;
	}
	else
		tmp_c = 0;
	if (c == '*' && tmp_c == 2)
		tmp_c = 3;
	if (c == '/' && tmp_c == 3){
		state_c = 0;
		tmp_c = 0;
	}
	else
		tmp_c = 2;
	return state_c;
}

int is_var(char *s){
	return !(is_string(s) || is_comment(s) || is_key_word(s));
}
