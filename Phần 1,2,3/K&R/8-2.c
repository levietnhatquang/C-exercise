#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PERMS 0666 //define permission linux style
#define EOF		(-1)
#define OPEN_MAX 20 //max # of _FILE open at the same time
#define NUM_TEST 1

typedef struct _flags{
	int _READ;
	int _WRITE;
	int _UNBUF;// _FILE is unbuffered
	int _EOF;	// EOF occur
	int _ERR;	// error in this _FILE
}flags;

enum _flag{
	_READ 	= 01,
	_WRITE 	= 02,
	_UNBUF 	= 04,	// file is unbuffered
	_EOF	= 010,	// EOF occur
	_ERR	= 020	// error in this file
};

typedef struct _iobuf{
	int cnt;	// char left
	char *ptr;	// next char pos
	char *base;	// buff location
	int flag;	// _FILE access mode
	int fd;		// _FILE descriptor
}_FILE;

typedef struct __iobuf{
	int cnt;	// char left
	char *ptr;	// next char pos
	char *base;	// buff location
	struct _flags flag;	// _FILE access mode
	int fd;		// _FILE descriptor
}_FILE_i;

extern _FILE _iob[OPEN_MAX] = {
	{0, (char *) 0, (char *) 0, _READ, 0},
	{0, (char *) 0, (char *) 0, _WRITE, 1},
	{0, (char *) 0, (char *) 0, _WRITE|_UNBUF, 2}
};

extern _FILE_i _iob_i[OPEN_MAX] = {
	{0, (char *) 0, (char *) 0, _READ, 0},
	{0, (char *) 0, (char *) 0, _WRITE, 1},
	{0, (char *) 0, (char *) 0, _WRITE|_UNBUF, 2}
};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

char _fillbuf(_FILE *);
char _fillbuf_i(_FILE_i *);
_FILE *_fopen(char *name, char *mode);
_FILE_i *_fopen_i(char *name, char *mode);
int is_empty(struct _flags flags);
//int _flushbuf(int, _FILE *);

#define feof(p)		((p->flag & _EOF) != 0)
#define ferror(p)	((p->flag & _ERR) != 0)
#define _FILEno(p)	(p->fd)



#define getc(p)		(--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ \
										: _fillbuf(p))
#define getc_i(p)	(--(p->cnt) >= 0 ? ((unsigned char) *p->ptr++) \
										: _fillbuf_i(p))
#define putc(x, p)	(--(p)->cnt >= 0 ? *(p)->ptr++ = x \
										: _flushbuf(x, p))
//#define getchar()	getc(stdin)
//#define putchar(x)	putc(x, stdout)

// fopen: open _FILE, return _FILE ptr
int main(void){
	clock_t t1 = clock();
 	_FILE *fp = _fopen("1-1.c","r");

	if (fp!=NULL){	
		char c;
		while ( ( c = getc(fp) ) != EOF ){
			// printf(" -%d- ", fp->cnt);
			// printf("%d", c);		
			//putchar(c);
			//putchar('*');
		}
	}
	else
		puts("Error");
	clock_t t2 = clock();

	clock_t t3 = clock();
	_FILE_i *fp_i = _fopen_i("8-2.c","r");

	if(fp_i!=NULL){	
		char c;
		while ((c=getc_i(fp_i))!=EOF){
			//putchar(c);
		}
	}
	else{
		puts("Error");
	}
	clock_t t4 = clock();

	printf("%s: %fx\n", "Time compare", (float) (t2 - t1)/(t4 - t3));

	return 0;
}

_FILE *_fopen(char *name, char *mode)
{
	int fd;
	_FILE *fp;
// printf("1");
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
// printf("2");
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ|_WRITE)) == 0)
			break; //found free slot
// printf("3");
	if (fp >= _iob + OPEN_MAX) //reach max number of _FILE to open
		return NULL;
// printf("4");
	if (*mode == 'w'){
		fd = creat(name, PERMS); // create new _FILE/overwrite old one
	}
	else if (*mode == 'a'){
// printf("5");
		if ((fd = open(name, 1, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0, 2); //go to the end of the _FILE => for what?
	}
	else{
		fd = open(name, O_RDONLY, 0);
	}
// printf("6");
	if (fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
// printf("7-");
	return fp;
}

// _fillbuf: allocate and fill input buffer
char _fillbuf(_FILE *fp)
{
	int bufsize;
// printf("8");
	if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag&_UNBUF) ? 1 : BUFSIZ;
// printf("9");
	if (fp->base == NULL) //no buffer yet
		if((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF; //cannot get buffer
// printf("10");
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
// printf("11\n");
	if (--fp->cnt < 0){
		if (--fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

_FILE_i *_fopen_i(char *name, char *mode)
{
	int fd;
	_FILE_i *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (is_empty(fp->flag))
			break; //found free slot

	if (fp >= _iob + OPEN_MAX) //reach max number of _FILE to open
		return NULL;

	if (*mode == 'w'){
		fd = creat(name, PERMS); // create new _FILE/overwrite old one
	}
	else if (*mode == 'a'){
		if ((fd = open(name, 1, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0, 2); //go to the end of the _FILE => for what?
	}
	else{
		fd = open(name, O_RDONLY, 0);
	}

	if (fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	if (*mode == 'r')
		fp->flag._READ = 1;
	else
		fp->flag._WRITE = 1;
	return fp;
}

// _fillbuf: allocate and fill input buffer
char _fillbuf_i(_FILE_i *fp)
{
	int bufsize;

	if (fp->flag._READ == 0)
		return EOF;
	bufsize = (fp->flag._UNBUF != 0) ? 1 : BUFSIZ;

	if (fp->base == NULL) //no buffer yet
		if((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF; //cannot get buffer

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);

	if (--fp->cnt < 0){
		if (--fp->cnt == -1)
			fp->flag._EOF = 1;
		else
			fp->flag._ERR = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int is_empty(struct _flags flags){
	if(!flags._READ && !flags._WRITE && !flags._UNBUF &&
			!flags._EOF && !flags._ERR)
		return 1;
	return 0;
}
/*
 * output
 *
 * quanglvn@quanglvn:~/1$ gcc 8-2.c -o 8-2
 * quanglvn@quanglvn:~/1$ ./8-2
 * Time compare: 1.831169x
 */











