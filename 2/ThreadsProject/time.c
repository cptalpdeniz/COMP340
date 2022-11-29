/*
*       COMP340 - Operating Systems
*       Assignment 2
*       Group 2
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "gui2.h"


typedef struct data {
	int tid;
	pthread_mutex_t *mutex;
	pthread_cond_t *cond;
} data;

typedef struct gui_data {
	int bin;
	int *done;
	pthread_mutex_t *mutex;
	pthread_cond_t *cond;
} gui_data;

/*
*	Due to failed attempts by teammates, we were not able to do a proper lottery algorithm. This following code randomizes the thread run order however this does not have any prioritization.
*	The biggest feature of the lottery algorithm is the prioritization. And, unfortunately, the following code does not have that implemented. It does randomize the scheduling order but it's not the implementation of the lottery algorithm.
*	Technically it is lottery algorithm, however in this function, every thread has equal chance of running, hence the lack of prioritization
*/
void randomizeOrder(data *data_array, int n)
{
    srand((unsigned)time(NULL));

    for (int i = 0; i < n - 1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        data t = data_array[j];
        data_array[j] = data_array[i];
        data_array[i] = t;
    }
}

void *thread_function(void *args)
{
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 100000000;
	
	pthread_t t, t2;
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_t cond;
	pthread_cond_init(&cond, NULL);


	data *thread_data = (data*)args;
	
	gui_data *threadData = (gui_data*)malloc(sizeof(gui_data));
	threadData->bin = thread_data->tid;
	threadData->done = (int*)malloc(sizeof(int));
	*(threadData->done) =  0;
	threadData->mutex = &mutex;
	threadData->cond = &cond;
	
	//instead of tracking the counter for the iteration with a variable, we implemented a simpler counting mechanism in the thread itself with a explicit var
	for (int i = 0; i < 2; ++i)
	{
		*(threadData->done) = 0;
		pthread_mutex_lock(&mutex);
		if (i == 0)
		{
			pthread_create(&t, NULL, gui, threadData);
		}
		else if (i == 1)
		{
			pthread_create(&t2, NULL, gui, threadData);
		}

		if (threadData->done == 0)
		{
			pthread_cond_wait(threadData->cond, threadData->mutex);
		}

		nanosleep(&ts, NULL); 
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		pthread_join(i == 0 ? t : t2, NULL);
	}

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	free(threadData->done);
	free(threadData);
	pthread_exit(NULL);
}

int main()
{
	int n = 100;
	pthread_t tid[n];
	data args[n];

	for (int i = 0; i < n; i++)
	{
		args[i].tid = i;
	}

	randomizeOrder(args, n);
	
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 100000000;

	for (int i = 0; i < n; ++i)
	{
		args[i].tid = i;
		nanosleep(&ts, NULL); //do not hog the CPU
		pthread_create(&tid[i], NULL, thread_function, &args[i]);
	}
	for (int i = 0; i < n; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	return EXIT_SUCCESS;
}

