#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	pid_t pid;
	if((pid = fork()) > 0)
	{
		printf("Parent; PID = %d, Child PID = %d, PPID = %d\n", getpid(), pid, getppid());
		exit(10);
	}
	
	else if(pid == 0)
	{
		printf("Child; PID = %d, Child PID = %d, PPID = %d\n", getpid(), pid, getppid());
		sleep(4); //for parent to finish before child
		printf("Child; PID = %d, Child PID = %d, PPID = %d\n", getpid(), pid, getppid());
		exit(1);
	}
	
	else
	{
		printf("Child creation failed\n");
		exit(0);
	}
}
		
