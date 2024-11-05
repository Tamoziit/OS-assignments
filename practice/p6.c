#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s <low> <high>\n", argv[0]);
		return 1;
	}
	
	int low = atoi(argv[1]);
	int high = atoi(argv[2]);
	int i, sum_res = 0;
	int exitstatus;
	pid_t pid;
	
	if((pid = fork()) == 0) // child process
	{
		printf("Child; PID = %d, PPID = %d\n", getpid(), getppid());
		for(i=low; i<=high; i++)
		{
			sum_res+=i;
		}
		printf("Sum = %d\n", sum_res);
		
		exit(sum_res);
	}
	
	else if(pid > 0) // parent process
	{
		wait(&exitstatus);
		int num = WEXITSTATUS(exitstatus);
		printf("Parent; PID = %d, Child PID = %d, PPID = %d\n", getpid(), pid, getppid());
		
		int c = 0;
		for(i=3; i<sqrt(num); i++)
		{
			if(num % i == 0)
				c++;
		}
		
		if(c != 0)
			printf("%d is Prime No.\n", num);
		else
			printf("%d is Not a Prime No.\n", num);
			
		exit(1);
	}
	
	else {
		printf("Error in child creation\n");
		exit(0);
	}
	
	return 0;
}
