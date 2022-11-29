/*
*	COMP340 - Operating Systems
*	Assignment 1
*	Group 2
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <process.h>
#include "graph.h"
#include "linked_list.h"

int totalconnections(Graph* G, int u, int v)
{
	bool thevisitedvertex[v];
	
	int count = 0;
	for (int u = 0; u < v; v++)
	{
		thevisitedvertex[v] = false;
	}
	for (int u = 0; u < v; v++)
	{
		if (thevisitedvertex[v] == false)
		{
			count = count + 1;
		}
	}
	return count;
}


int main()
{
	Graph *G = malloc(sizeof(Graph) * 4);
	G = createGraph(4);
	connect(G, 0, 1);
	connect(G, 0, 2);
	connect(G, 1, 2);
	connect(G, 2, 3);
	connect(G, 3, 4);

	printf("Running SECOND PROGRAM. Counting the total number of connections in the Graph G. Graph G is:\n");
	printGraph(G);
	printf("\nRunning program...Graph G has %d connections",totalconnections(G,0,1));
	return EXIT_SUCCESS;
}
