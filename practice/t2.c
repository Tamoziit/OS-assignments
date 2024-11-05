#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#define MAX 10

int threads_created = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread_ops(void* threadargs)
{
	int thread_data = *(int*)threadargs;
	pthread_t sid;
	
	pthread_mutex_lock(&mutex1);
	sid = pthread_self();
	printf("Thread %d, TID = %lu\n", thread_data, sid);
	pthread_mutex_unlock(&mutex1);
	
	if(threads_created != 1)
		wait(NULL);
		
	pthread_exit((void*)(long)sid);
}

int main()
{
	pthread_t thread;
	int thread_data[MAX];
	int status;
	void* retval;
	
	int i;
	for(i=0; i<MAX; i++)
	{
		thread_data[i] = i+1;
		if(threads_created == 0)
		{
			if((status = pthread_create(&thread, NULL, &thread_ops, (void*)&thread_data[i])))
			{
				printf("Thread creation failed\n");
				exit(1);
			}
			
			threads_created++;
		}
		
		if(threads_created == 1)
		{
			pthread_mutex_lock(&mutex2);
			pthread_join(thread, &retval);
			printf("Thread %d exited with retval = %lu\n", i+1, retval);
			threads_created--;
			pthread_mutex_unlock(&mutex2);
		}
	}
	
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
	pthread_exit(NULL);
}
