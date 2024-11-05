#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#define MAX 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
int threads_created = 0;

void *thread_ops(void* threadargs)
{
	int thread_data = *(int*)threadargs;
	pthread_t sid;
		
	pthread_mutex_lock(&mutex1);
	sid = pthread_self();
	printf("Thread %d, TID = %lu\n", thread_data, sid);
	pthread_mutex_unlock(&mutex1);
		
	if(threads_created != thread_data)
	{
		wait(NULL);
	}
	pthread_exit((void*)(long)sid);
}

int main()
{
	pthread_t threads[MAX];
	int threads_data[MAX];
	int status;
	void *retval;
	
	int i;
	for(i=0; i<MAX; i++)
	{
		threads_data[i] = i+1;
		if((status = pthread_create(&threads[i], NULL, &thread_ops, (void*)&threads_data[i])))
		{
			printf("Error in thread creation\n");
			exit(1);
		}
		threads_created++;
	}
	
	if(threads_created == MAX)
	{
		for(i=0; i<MAX; i++)
		{
			pthread_mutex_lock(&mutex2);
			pthread_join(threads[i], &retval);
			printf("Thread %d exited with val = %lu\n", i+1, (long)retval);
			threads_created--;
			wait(NULL);
			pthread_mutex_unlock(&mutex2);
		}
	}
	
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
	pthread_exit(NULL);
}
