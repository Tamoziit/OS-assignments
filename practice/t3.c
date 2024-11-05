#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int val = 0;

void* inc(void* threadargs)
{
	int n = *(int*)threadargs;
	pthread_t sid;

	while(1)
	{
		if(val < 10)
		{
			pthread_mutex_lock(&mutex);
			sid = pthread_self();
			val++;
			printf("Thread %d, ID = %lu; Incrementing: %d\n", n, sid, val);
			pthread_mutex_unlock(&mutex);
		} else {
			sleep(2);
			printf("Thread %d Waiting\n", n); //busy waiting
		}
	}

	pthread_exit((void*)(long)sid);
}

int main()
{
	pthread_t threads[2];
	int thread_data[2];
	int status, i;
	void* retval;
	
	for(i=0; i<2; i++)
	{
		thread_data[i] = i+1;
		if((status = pthread_create(&threads[i], NULL, &inc, (void*)&thread_data[i])))
		{
			printf("Thread %d creation failed\n", thread_data[i]);
			exit(1);
		}
	}
	
	for(i=0; i<2; i++)
	{
		pthread_join(threads[i], &retval);
		printf("Thread %d exited with val = %lu\n", thread_data[i], retval);
	}
	
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
	return 0;
}
