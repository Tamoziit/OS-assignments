#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1 = getpid(); // parent pid
    pid_t pid2, pid3;
    
    pid2 = fork(); // creating child process
    
    if(pid2 < 0) {
        printf("Couldn't create child process\n");
        return 1;
    }
    
    if (pid2 == 0) {
        pid2 = getpid();
    
        pid3 = fork(); // creating grandchild process
        if(pid3 < 0) {
            printf("Couldn't create grandchild process\n");
            return 1;
        }
        
        if(pid3 == 0) {
            // Grandchild process
            pid3 = getpid();
            printf("Grandchild process-> PID: %d, PPID: %d, Parent of PPID: %d\n", pid3, getppid(), pid1);
            exit(0); // grandchild process ends
        } else {
            // Child process (parent of grandchild)
            wait(NULL); // waiting for grandchild to finish
            printf("Child Process-> PID: %d, PPID: %d, Child process: %d\n", pid2, getppid(), pid3);
            exit(0); // child process ends
        }
    } else {
        // Parent process
        wait(NULL); // waiting for child to finish
        printf("Parent process: PID: %d, Child PID: %d\n", pid1, pid2);
    }
    
    return 0;
}

