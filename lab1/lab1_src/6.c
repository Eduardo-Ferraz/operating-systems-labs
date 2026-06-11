#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int glob = 6;
int main(void) {
	int var;
	pid_t pid;
	var = 88;
	printf("before fork\n");
	if ((pid = fork()) < 0) 
		fprintf(stderr, "fork error\n");
    	else 
        	if (pid == 0) 
        	{ 
			glob++;
			var++;
            		//change child PGID to var value
			if (setpgid(0, var) != 0) 
				perror("setpgid failed");
		
		}       
    		else 
			sleep(15); 
	printf("pid = %d, ppid = %d, glob = %d, var = %d, uid = %d, pgid = %d\n", getpid(), getppid(), glob, var, getuid(), getpgrp());

	return 0;
}
