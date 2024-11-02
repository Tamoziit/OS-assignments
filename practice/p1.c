#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	printf("Main method; PID = %d\n", getpid());
	pid_t pid = fork();
	
	if(pid < 0)
	{
		printf("Couldn't create Child process\n");
		return 1;
	}
	
	if(pid > 0)
	{
		pid = getpid();
		printf("Parent Process; Self ID = %d, Parent PID = %d\n", pid, getppid());
	}
	
	if(pid == 0)
	{
		pid = getpid();
		printf("Child Process; Self ID = %d, Parent PID = %d\n", pid, getppid());
	}
	
	return 0;
}
