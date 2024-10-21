#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_THREADS 10

// Global variable to track the number of created threads & mutex
int threads_created = 0;
int mutex = 0;

// Thread function
void* print_hello(void* threadarg) {
	mutex = 0;
    int thread_id = *(int*)threadarg;
    
    printf("Hello from thread %d, Thread id = %ld\n", thread_id, pthread_self());
    
    // Returning thread ID to the main thread
    pthread_exit((void*)(long)thread_id);
}	

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_data[NUM_THREADS];
    void* status;

    // Create all threads first
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i] = i + 1; // Thread IDs start from 1
        mutex = 1;
        if(mutex) {
        	wait(NULL);
        }
        pthread_create(&threads[i], NULL, print_hello, (void*)&thread_data[i]);
        // Increment the count of created threads
        threads_created++;
    }

    // Wait for all threads to complete and print their return values
    for (int i = 0; i < NUM_THREADS; i++) {
        if(threads_created != NUM_THREADS - 1 - i)
        {
        	wait(NULL);
        }
        --threads_created;
        pthread_join(threads[i], &status);
        printf("Thread %d has finished with return value: %ld\n", i + 1, (long)status);
    }

    pthread_exit(NULL); // Exit main thread
}
