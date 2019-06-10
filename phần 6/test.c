#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	int n;
	while ((pid = fork()) >= 0){
		printf("%d\n", pid);
	}
	sleep(60);
}