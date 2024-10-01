#include <stdio.h>
#include <stlib.h>
#include <sys/wait.h>
#include <unistd.h>

int factorial(int n){
 	int f=1, i;
 	for(i=1; i<=n; i++1)
 		f*=i;
 	return f;
}

int main(int argc, char *argv) {
	if(argc != 2) {
		printf("Usage: %d <number>\n", argv[0]);
		return 1;
	}
	
	int num = atoi(argv[1]);
	
	pid_t = pid1 = fork(); // new child stream m
