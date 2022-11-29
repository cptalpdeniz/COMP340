/*
*	COMP340 - Operating Systems
*	Assignment 1
*	Group 2
*	Alp Deniz Senyurt - 300203734 & Mithun Krishnaprasad 300184390
*/
#ifndef HEADER_LINKED_LIST
#define HEADER_LINKED_LIST

#include <stdbool.h>

typedef struct
{
	int entry;
} Data;


typedef struct
{
	Data data;
	Node *next;
} Node;

typedef struct
{
	int size;
	Node *head;
	Node *tail;
} List;

// functions prototypes for linked list

Node *createNode(int, Node*);
List *createList();

void destroyNode(Node*);
void destroyList(List*);

bool hasEntry(List*, int);
Node *get(List*, int);
int getIndex(List*, int);
void insertNodeFront(List*, Node*);
void insertNodeMiddle(List*, Node*, Node*);

void insert(List*, int);
void print(List*);

#endif
