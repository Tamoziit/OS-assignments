#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int globalvble = 10;

int main()
{
	pid_t retval;
	int localvble = 20;
	int childretval;
	int exitstatus, i=0;
	
	if((retval = fork()) >= 0)
	{
		if(retval == 0)
		{
			printf("Child; retval = %d, PID = %d, PPID = %d\n", retval, getpid(), getppid());
			while(i<10) {
				printf("Child; i = %d, localvble = %d, globalvble = %d\n", i, localvble, globalvble);
				++localvble;
				++globalvble;
				++i;
			}
			
			printf("Child; enter exit val:\n");
			scanf("%d", &childretval);
			printf("Child End\n");
			exit(childretval);
		}
		
		else if(retval > 0)
		{
			sleep(4);
			printf("Parent; Child PID = %d, PID = %d, PPID = %d\n", retval, getpid(), getppid());
			while(i<20) {
				printf("Parent; i = %d, localvble = %d, globalvble = %d\n", i, localvble, globalvble);
				++localvble;
				++globalvble;
				++i;
			}
			
			sleep(2);
			wait(&exitstatus);
			printf("Parent: Child exited with code = %d\n", WEXITSTATUS(exitstatus));
			printf("Parent End\n");
			exit(0);
		}
	} else {
		printf("Child creation failed\n");
		exit(1);
	}
}
