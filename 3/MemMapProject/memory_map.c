/*
	COMP340 - Operating Systems
	Assignment 3
	Group 1
	Alp Deniz Senyurt - 300203734 & Mithun Krishnaprasad 300184390 & Shengfu Wang - 
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/mman.h>
#include <pthread.h>
#include <unistd.h>

#define PAGE_SIZE 4096
#define BUFFER_N_PAGES 1

typedef struct {
	int buffer;
	pthread_cond_t condc, condp;
	pthread_mutex_t mutex;
} Data;

void _producer(Data *data) 
{
	int count = 0;

	while (data->buffer >= 0 && data->buffer < 100)
	{
		pthread_mutex_lock(&data->mutex);

		count++;
		data->buffer = count;
		printf("Producer: I've produced the number = %d\n", count);

		pthread_cond_signal(&data->condc);
		pthread_cond_wait(&data->condp, &data->mutex);

		pthread_mutex_unlock(&data->mutex);

		struct timespec ts;
		ts.tv_sec = 1;
		ts.tv_nsec = 000000000;
		nanosleep(&ts, 0);	
	}
}

void _consumer(Data *data) 
{
	int number = 0;

	while (data->buffer >= 0 && data->buffer < 100) {

		pthread_mutex_lock(&data->mutex);
		pthread_cond_wait(&data->condc, &data->mutex);

		number = data->buffer;
		data->buffer--;

		printf("Consumer: I consumed the number = %d\n", number);

		pthread_cond_signal(&data->condp);
		pthread_mutex_unlock(&data->mutex);
	}
}

int main() 
{

	Data *data =
	mmap(
				NULL, //hint address, otherwise the OS assigns this
				BUFFER_N_PAGES * PAGE_SIZE, //mapped size region
				PROT_READ | PROT_WRITE,     //protection bits
				MAP_ANONYMOUS | MAP_SHARED, //flags
				-1, // fd, but anonymous flag will then make mmap ignore this
				0   // offset
				);

	if (data == MAP_FAILED)
	{
		fprintf(stderr, "ERROR: Memory Map failed.\n");
		exit(EXIT_FAILURE);
	}

	pthread_mutexattr_t mutexattr;
	pthread_condattr_t condattr1, condattr2;

	pthread_mutexattr_init(&mutexattr);
	pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&data->mutex, &mutexattr);

	pthread_condattr_init(&condattr1);
	pthread_condattr_setpshared(&condattr1, PTHREAD_PROCESS_SHARED);
	pthread_cond_init(&data->condc, &condattr1);

	pthread_condattr_init(&condattr2);
	pthread_condattr_setpshared(&condattr2, PTHREAD_PROCESS_SHARED);
	pthread_cond_init(&data->condp, &condattr2);

	//get PID
	pid_t pid;
	pid = fork();
	if (pid != 0) 
	{
		if (pid == -1)
		{
			fprintf(stderr, "ERROR: fork() failed.\n");
			pthread_mutex_destroy(&data->mutex);
			munmap(data, BUFFER_N_PAGES * PAGE_SIZE);
			exit(EXIT_FAILURE);
		}

		pthread_mutex_lock(&data->mutex);
		pthread_mutex_unlock(&data->mutex);

		_consumer(data);
	}
	else 
	{
		_producer(data);
	}

	pthread_cond_destroy(&data->condp);
	pthread_cond_destroy(&data->condc);
	pthread_mutex_destroy(&data->mutex);
	munmap(data, BUFFER_N_PAGES * PAGE_SIZE);

	return EXIT_SUCCESS;
}
