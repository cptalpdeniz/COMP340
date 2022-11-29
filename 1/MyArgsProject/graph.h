/*
*	COMP340 - Operating Systems
*	Assignment 1
*	Group 2
*	Alp Deniz Senyurt - 300203734 & Mithun Krishnaprasad 300184390
*/
#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include "linked_list.h"

typedef struct Graph
{
	int n;
	List **A;
} Graph;

Graph *createGraph(int);
void destroyGraph(Graph*);

Graph *getTree(int[], int);

void connect(Graph*, int, int);
void printGraph(Graph*);

Graph *breadthSearch(Graph*, int);

#endif