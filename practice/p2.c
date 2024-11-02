#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid1, pid2, pid3;
	pid1 = getpid();
	
	pid2 = fork();
	if(pid2 < 0)
	{
		printf("Couldn't create child process\n");
		return 1;
	}
	
	if(pid2 == 0) //Child Process
	{
		pid2 = getpid();
		
		pid3 = fork();
		if(pid3 < 0)
		{
			printf("Couldn't create grandchild process\n");
			return 1;
		}
		
		if(pid3 == 0) //grandchild process
		{
			pid3 = getpid();
			printf("Grandchild Process --> PID: %d, PPID: %d, Parent of PPID: %d\n", pid3, getppid(), pid1);
			exit(0);
		} else {
			//Child Process
			wait(NULL);
			printf("Child Process --> PID: %d, PPID: %d, Child Process: %d\n", pid2, getppid(), pid3);
			exit(0);
		}
	} else {
		//Parent Process
		wait(NULL);
		printf("Parent Process --> PID: %d, Child Process: %d\n", pid1, pid2);
	}
	
	return 0;
}
			
