#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	printf("Parent Process: %d\n", getpid());
	
	pid = fork();
	if(pid == 0)
	{
		printf("Child; PID = %d, PPID = %d\n", getpid(), getppid());
		exit(0);
	}
	
	while(1) { // infinite waiting for child
		sleep(1);
		printf("Waiting!\n");
	}
	
	return 0;
} 
