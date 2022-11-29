/*
*       COMP340 - Operating Systems
*       Assignment 2
*       Group 4
*       Alp Deniz Senyurt - 300203734 & Mithun Krishnaprasad 300184390 & Urvashi & Shengfu Wang
*		Please keep in mind that almost NO CODE was written by Urvashi and Shengfu Wang. We split tasks evenly and talked for days in the group chat however they were not able to deliver ANYTHING at all. I hope this is taken into consideration when assignment is marked.
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
