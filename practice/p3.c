#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

long factorial(int n)
{
	int i;
	long res = 1;
	for(i=1; i<=n; i++)
	{
		res*=i;
	}
	
	return res;
}

int main(int argc, char *argv[])
{
	pid_t pid;
	if(argc != 2)
	{
		printf("Usage: %s <number>\n", argv[0]);
		return 1;
	}
	
	int num = atoi(argv[1]);
	int i;
	pid = fork();
	
	if(pid < 0)
	{
		printf("Child Creation failed\n");
		return 1;
	}
	
	if(pid == 0) //Child Process
	{
		pid = getpid();
		long sum = 0;
		for(i=1; i<=num; i++)
		{
			sum += factorial(i);
		}
		
		printf("Summation = %ld\n", sum);
		printf("Child Process; PID = %d, PPID = %d\n", pid, getppid());
		exit(0);
	} else { //Parent Process
		wait(NULL);
		//wait(NULL);
		
		pid = getpid();
		long res = factorial(num);
		printf("Factorial = %ld\n", res);
		printf("Parent Process; PID = %d, PPID = %d\n", pid, getppid());
		exit(0);
	}
	
	return 0;
}
