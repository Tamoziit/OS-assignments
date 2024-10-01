#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

// Function to check if a number is prime
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to report even and odd numbers in the range
void report_even_odd(int min, int max) {
    printf("Process 1 (PID: %d): Reporting even and odd numbers from %d to %d\n", getpid(), min, max);
    for (int i = min; i <= max; i++) {
        if (i % 2 == 0) {
            printf("Even: %d\n", i);
        } else {
            printf("Odd: %d\n", i);
        }
    }
}

// Function to report prime and non-prime numbers in the range
void report_prime_non_prime(int min, int max) {
    printf("Process 2 (PID: %d): Reporting prime and non-prime numbers from %d to %d\n", getpid(), min, max);
    for (int i = min; i <= max; i++) {
        if (is_prime(i)) {
            printf("Prime: %d\n", i);
        } else {
            printf("Non-Prime: %d\n", i);
        }
    }
}

// Function to calculate the summation of even and prime numbers in the range
void sum_even_prime(int min, int max) {
    int even_sum = 0, prime_sum = 0;
    printf("Process 3 (PID: %d): Calculating summation of even and prime numbers from %d to %d\n", getpid(), min, max);
    for (int i = min; i <= max; i++) {
        if (i % 2 == 0) {
            even_sum += i;
        }
        if (is_prime(i)) {
            prime_sum += i;
        }
    }
    printf("Summation of even numbers: %d\n", even_sum);
    printf("Summation of prime numbers: %d\n", prime_sum);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <min> <max>\n", argv[0]);
        return 1;
    }

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);

    pid_t pid1, pid2, pid3;
    int status;

    // First process: report even and odd numbers
    if ((pid1 = fork()) == 0) {
        // Child process 1
        report_even_odd(min, max);
        exit(0);
    } else if (pid1 < 0) {
        perror("Fork failed for process 1");
        return 1;
    }

    // Second process: report prime and non-prime numbers
    if ((pid2 = fork()) == 0) {
        // Child process 2
        report_prime_non_prime(min, max);
        exit(0);
    } else if (pid2 < 0) {
        perror("Fork failed for process 2");
        return 1;
    }

    // Third process: summation of even and prime numbers
    if ((pid3 = fork()) == 0) {
        // Child process 3
        sum_even_prime(min, max);
        exit(0);
    } else if (pid3 < 0) {
        perror("Fork failed for process 3");
        return 1;
    }

    // Parent process waits for all child processes to complete
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    waitpid(pid3, &status, 0);

    printf("Parent Process (PID: %d): All child processes have completed.\n", getpid());

    return 0;
}

