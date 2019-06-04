#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


#define MAX_PATH 1024

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

int main(int argc, char *argv[]){
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

void fsize(char * name){ 
	struct stat stbuf;
	
	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	printf("%8ld %s [Inode: %ld Links: %hd UID: %hd GID: %hd]\n", (long) stbuf.st_size, name, (long) stbuf.st_ino, (short) stbuf.st_nlink, (short) stbuf.st_uid, (short) stbuf.st_gid);
}

void dirwalk(char *dir, void (*fcn)(char *)){
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;
	
	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0
		  || strcmp(dp->d_name, "..") == 0)
			continue;
		if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}
/* output
 * quanglvn@quanglvn:~/1$ gcc 8-5.c -o 8-5
 * quanglvn@quanglvn:~/1$ ./8-5 1-1.c
 *      509 1-1.c [Inode: 9183210 Links: 1 UID: 1000 GID: 1000]
 * quanglvn@quanglvn:~/1$
 */