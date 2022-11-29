/*
*	COMP340 - Operating Systems
*	Assignment 1
*	Group 2
*	Alp Deniz Senyurt - 300203734 & Mithun Krishnaprasad 300184390
*
*	Contains code from Graph example, courtesy of Dr Russell Campbell
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

Graph *createGraph(int n)
{
	Graph *G = (Graph*)malloc(sizeof(Graph));
	G->n = n;
	G->A = (List**)malloc(sizeof(List*) * n);
	for (int i = 0; i < n; i++)
	{
		G->A[i] = createList();
	}
	return G;
}

void destroyGraph(Graph *G)
{
	for(int i = 0; i < G->n; i++)
	{
		destroyList(G->A[i]);
	}
	free(G->A);
}

Graph *getTree(int parents[], int n)
{
	Graph *T = createGraph(n);
	for (int i = 0; i < n; i++)
		connect(T, i, parents[i]);

	return T;
}

void connect(Graph* G, int u, int v)
{
	if (u == v)
		return;
	
	if (hasEntry(G->A[u], v)) 
	{
		if (hasEntry(G->A[v], u))
			return;
		else 
		{
			insert(G->A[v], u);
			return;
		}
	}
	else
	{
		if (hasEntry(G->A[v], u)) 
		{
			insert(G->A[u], v);
			return;
		}
	}

	
	insert(G->A[u], v);
	insert(G->A[v], u);
}

void printGraph(Graph *G)
{
	for (int i = 0; i < G->n; i++)
	{
		printf("[%d]:", i);
		print(G->A[i]);
	}
	printf("\n");
}

Graph *breadthSearch(Graph* G, int u)
{
	int queue[G->n];
	bool visited[G->n];
	int parents[G->n];
	int front = 0;

	queue[front] = u;
	parents[u] = u;
	int back = front + 1;

	while (back < G->n)
	{
		int v = queue[front];
		for (int i = 0; i < G->A[v]->size ; i++)
		{
			int w = getIndex(G->A[v], i);
			if (!visited[w])
			{
				visited[w] = true;
				queue[back++] = w;
				parents[w] = v;
			}
		}
		front++;
	}
	return getTree(parents, G->n);
}