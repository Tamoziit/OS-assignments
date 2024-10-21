#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 10

// Global variables
pthread_mutex_t mutex; // Mutex for synchronization
int threads_created = 0; // Counter for created threads

// Thread function
void* print_hello(void* threadarg) {
    int thread_id = *(int*)threadarg;

    // Lock the mutex to ensure synchronized access
    pthread_mutex_lock(&mutex);
    
    // Wait until all threads are created
    while (threads_created < NUM_THREADS) {
        pthread_mutex_unlock(&mutex); // Unlock before sleeping to avoid deadlock
        usleep(100); // Sleep for a short time to prevent busy waiting
        pthread_mutex_lock(&mutex); // Lock again to check the condition
    }

    printf("Hello from thread %d, Thread id = %ld\n", thread_id, pthread_self());

    pthread_mutex_unlock(&mutex); // Unlock after printing

    // Returning thread ID to the main thread
    pthread_exit((void*)(long)thread_id);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_data[NUM_THREADS];
    void* status;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create all threads first
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i] = i + 1; // Thread IDs start from 1
        pthread_create(&threads[i], NULL, print_hello, (void*)&thread_data[i]);
        
        // Increment the count of created threads under mutex protection
        pthread_mutex_lock(&mutex);
        threads_created++;
        pthread_mutex_unlock(&mutex);
    }

    // Wait for all threads to complete and print their return values
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &status);
        printf("Thread %d has finished with return value: %ld\n", i + 1, (long)status);
    }

    // Destroy the mutex after use
    pthread_mutex_destroy(&mutex);

    pthread_exit(NULL); // Exit main thread
}
