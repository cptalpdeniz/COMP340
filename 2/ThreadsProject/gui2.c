/*
*       COMP340 - Operating Systems
*       Assignment 2
*       Group 4
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#include "display.h"

#define PI2 6.28318530717

typedef struct gui_data {
	int bin;
	int *done;
	pthread_mutex_t *mutex;
	pthread_cond_t *cond;
} gui_data;

void *gui(void *count)
{
	gui_data *guiData = (gui_data*)count;

	pthread_mutex_lock(guiData->mutex);
	int x, y;
	char panel[HEIGHT][WIDTH];
	
	fill(panel);
	x = ((guiData->bin / 10) % 10);
	y = (guiData->bin % 10);
	set(panel, x, y, 'X');
	
	system("clear");
	display(panel);
	
	printf("\n");
	
	*(guiData->done) = 1;
	pthread_mutex_unlock(guiData->mutex);
	pthread_exit(NULL);
}
