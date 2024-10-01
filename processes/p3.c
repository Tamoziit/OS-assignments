#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

// Declaration of the global sum variable
int sum_res;

// Function to calculate the summation of all integers between low and high
int calculate_sum(int low, int high) {
    int sum = 0;
    for (int i = low; i <= high; i++) {
        sum += i;
    }
    return sum;
}

// Function to check if a number is prime
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Declare sum_res as an external variable
extern int sum_res;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <low> <high>\n", argv[0]);
        return 1;
    }

    int low = atoi(argv[1]);
    int high = atoi(argv[2]);

    pid_t pid_sum, pid_prime;
    int status;

    // First process to calculate the sum
    if ((pid_sum = fork()) == 0) {
        // Child process for summation
        sum_res = calculate_sum(low, high);
        printf("Summation Process (PID: %d, PPID: %d): Sum of integers from %d to %d is %d\n",
               getpid(), getppid(), low, high, sum_res);
        exit(0);
    } else if (pid_sum < 0) {
        perror("Fork failed for summation process");
        return 1;
    }

    // Wait for the summation process to finish
    wait(&status);

    // Second process to check if the sum is prime
    if ((pid_prime = fork()) == 0) {
        // Child process for prime evaluation
        bool prime_result = is_prime(sum_res);  // Accessing the global sum_res
        printf("Prime Check Process (PID: %d, PPID: %d): The sum %d is %s\n",
               getpid(), getppid(), sum_res, prime_result ? "prime" : "not prime");
        exit(0);
    } else if (pid_prime < 0) {
        perror("Fork failed for prime check process");
        return 1;
    }

    // Wait for the prime check process to finish
    wait(NULL);  // Wait for the second process

    // Parent process
    printf("Parent Process (PID: %d): Created child processes (Sum PID: %d, Prime Check PID: %d)\n",
           getpid(), pid_sum, pid_prime);

    return 0;
}

