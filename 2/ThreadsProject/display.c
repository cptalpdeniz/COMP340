/*
*       COMP340 - Operating Systems
*       Assignment 2
*       Group 4
*/

#include <stdio.h>
#include <string.h>
#include "display.h"

void set(char buf[HEIGHT][WIDTH], int i, int j, char c)
{
	buf[j][i] = c;
}


void fill(char buf[HEIGHT][WIDTH])
{
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			buf[j][i] = '`';
		}
	}
}


void display(char buf[HEIGHT][WIDTH])
{
	char frame[HEIGHT*(WIDTH+1)+1];
	
	copy_frame(frame, buf);
	
        printf("%s", frame);

}


void copy_frame(char f[], char b[HEIGHT][WIDTH])
{
	for (int i = 0; i < HEIGHT; i++)
	{
		strncpy(
			&(f[i*(WIDTH+1)]),
			b[i],
			WIDTH
		);
		f[i*(WIDTH+1) + WIDTH] = '\n';
	}
	f[HEIGHT*(WIDTH+1)] = '\0';
}
