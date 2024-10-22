#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_THREADS 10

// Global variable to track the number of created threads & mutex
int threads_created = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

// Thread function
void* thread_ops(void* threadarg) {
    int thread_data = *(int*)threadarg;
    pthread_t sid;
    
    pthread_mutex_lock(&mutex1);
    sid = pthread_self();
    printf("Hello from thread %d; Thread id = %lu\n", thread_data, sid);
    pthread_mutex_unlock(&mutex1);
    
    if(threads_created != thread_data)
    {
		wait(NULL);
    }
	// Returning thread ID to the main thread
	pthread_exit((void*)(long)sid);
}	

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_data[NUM_THREADS];
    int status;
    void *retval;

    // Creating all threads first
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i] = i + 1;
        if((status = pthread_create(&threads[i], NULL, &thread_ops, (void*)&thread_data[i])))
        {
        	printf("Error in creating thread %d\n", thread_data[i]);
        	exit(1);
        }
        threads_created++;
    }

    // Wait for all threads to complete and print their return values
    if(threads_created == NUM_THREADS)
    {
    	for (int i = 0; i < NUM_THREADS; i++) {
			pthread_mutex_lock(&mutex2);
        	pthread_join(threads[i], &retval);
        	printf("Thread %d has finished with return value: %lu\n", i + 1, (long)retval);
        	threads_created--;
        	wait(NULL);
		    pthread_mutex_unlock(&mutex2);
        }
    }
	
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
    pthread_exit(NULL); // Exit main thread
}
