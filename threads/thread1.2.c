#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_THREADS 10

int threads_created = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* thread_ops(void* threadarg) {
    int thread_data = *(int*)threadarg;
    pthread_t sid;
    
    pthread_mutex_lock(&mutex1);
    sid = pthread_self();
    printf("Hello from thread %d; Thread id = %lu\n", thread_data, sid);
    pthread_mutex_unlock(&mutex1);
    
    if(threads_created != 1)
    {
		wait(NULL);
    }

	pthread_exit((void*)(long)sid);
}	

int main() {
    pthread_t threads[1];
    int thread_data[NUM_THREADS];
    int status, i, x=0;
    void *retval;
    

    for (i = 0; i < NUM_THREADS; i++) {
    	if(threads_created != 0)
    		wait(NULL);

        thread_data[x] = i + 1;
        if((status = pthread_create(&threads[0], NULL, &thread_ops, (void*)&thread_data[x++])))
        {
        	printf("Error in creating thread %d\n", thread_data[x]);
        	exit(1);
        }
        
        threads_created++;

		if(threads_created == 1)
		{
				pthread_mutex_lock(&mutex2);
		    	pthread_join(threads[0], &retval);
		    	printf("Thread %d has finished with return value: %lu\n", i + 1, (long)retval);
		    	threads_created--;
				pthread_mutex_unlock(&mutex2);
		} else {
			wait(NULL);
		}
	}
	
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
    pthread_exit(NULL);
}
