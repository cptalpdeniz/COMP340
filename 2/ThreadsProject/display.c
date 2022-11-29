/*
*       COMP340 - Operating Systems
*       Assignment 2
*       Group 4
*       Alp Deniz Senyurt - 300203734 & Mithun Krishnaprasad 300184390 & Urvashi & Shengfu Wang
*		Please keep in mind that almost NO CODE was written by Urvashi and Shengfu Wang. We split tasks evenly and talked for days in the group chat however they were not able to deliver ANYTHING at all. I hope this is taken into consideration when assignment is marked.
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
