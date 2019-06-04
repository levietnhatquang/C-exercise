#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/file.h>

int main(int argc, char *argv[]){
	char buf[100];
	int f, n;
	if (argc != 2){
		perror("please use: ./8-1 <filename>");
		exit(EXIT_FAILURE);
	}
	if ((f = open(argv[1], O_RDONLY, 0)) == 1){
		perror("cat: cannot open 8-1.c");
		exit(EXIT_FAILURE);
	}
	else{
		while ((n = read(f, buf, 100)) > 0)
			write(1, buf, n);
		exit(EXIT_SUCCESS);
	}

	return 0;
}
/* output
 * quanglvn@quanglvn:~/1$ gcc 8-1.c -o 8-1
 * quanglvn@quanglvn:~/1$ ./8-1 8-1.c
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <errno.h>
 * #include <sys/file.h>
 * 
 * int main(int argc, char *argv[]){
 *         char buf[100];
 *         int f, n;
 *         if (argc != 2){
 *                 perror("please use: ./8-1 <filename>");
 *                 exit(EXIT_FAILURE);
 *         }
 *         if ((f = open(argv[1], O_RDONLY, 0)) == 1){
 *                 perror("cat: cannot open %s", argv[1]);
 *                 exit(EXIT_FAILURE);
 *         }
 *         else{
 *                 while ((n = read(f, buf, 100)) > 0)
 *                         write(1, buf, n);
 *                 exit(EXIT_SUCCESS);
 *         }
 * 
 *         return 0;
 * }
 * quanglvn@quanglvn:~/1$
 */