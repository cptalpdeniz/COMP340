/*
*	COMP340 - Operating Systems
*	Assignment 1
*	Group 2
*	Alp Deniz Senyurt - 300203734 & Mithun Krishnaprasad 300184390
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

bool checkIncreasingOrder(List* list)
{
	if (list->head == NULL || list->tail == NULL)
	{
		return false;
	}

	for (Node *n = list->head; n->next != NULL; n = n->next)
	{
		if (n->data->entry > n->next->data->entry)
		{
			return false;
		}
	}
	return true;
}

bool ifSorted(Graph *G)
{
	if (G->A == NULL)
	{
		return false;
	}

	int NUM = sizeof(G->A) / sizeof(G->A[0]);
	for (int i = 0; i < NUM; i++)
	{
		if (!checkIncreasingOrder(G->A[i]))
			return false;
	}
	return true;
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

	printf("Running FIRST PROGRAM. Checking if the Graph G is sorted in ascending order.\nFirst I will print the graph.\n");
	printGraph(G);
	printf("After checking if Graph G is sorted, the result is: %s", ifSorted(G) ? "true" : "false");
	return EXIT_SUCCESS;
}