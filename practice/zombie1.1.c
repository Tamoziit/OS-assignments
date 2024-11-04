#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	
	if((pid = fork()) == 0)
	{
		printf("Child; PID = %d, PPID = %d\n", getpid(), getppid());
		sleep(1);
		exit(1);
	}
	
	else if(pid > 0)
	{
		while(1) { // infinite wait
			printf("Parent; PID = %d, Child ID = %d\n", getpid(), pid);
			sleep(1);
		}
	}
	
	else {
		printf("Child Creation failed\n");
		exit(0);
	}
	
	return 0;
} 
