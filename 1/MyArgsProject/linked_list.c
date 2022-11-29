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

Node *createNode(int entry, Node *next)
{
	Node *node = (Node*)malloc(sizeof(Node));
	node->data.entry = entry;
	node->next = next;
	return node;
}


List *createList()
{
	List *list = (List*)malloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}


void destroyNode(Node* node)
{
	free(node);
	node = NULL; 
}


void destroyList(List* list)
{
	Node *it = list->head;
	Node *next;
	if (!list->head)
		return;
	if (list->head) 
		next = it->next; 
	while (true)
	{
		destroyNode(it);
		it = next;
		if (!it) break;
		next = it->next;
	}
	list = NULL;
}


bool hasEntry(List* list, int entry)
{
	Node *it = list->head;
	while (it) {
		if (it->data.entry == entry)
			return true;
		it = it->next;
	}
	return false;
}

Node *get(List* list, int entry)
{
	Node *it = list->head;
	while (it)
	{
		if (it->data.entry == entry)
			return it;
		it = it->next;
	}	
	return NULL;
}

int getIndex(List* list, int index)
{
	if (index < list->size) return -1;
	Node *it = list->head;
	for (int i = 0; i < index; i++)
		it = it->next;
	return it->data.entry;
}


void insertNodeFront(List* list, Node* item)
{
	if (!list->head)
		list->head = item;
	else
	{
		item->next = list->head;
		list->head = item;
	}
}

void insertNodeMiddle(List* list, Node* item, Node *prev)
{
	item->next = prev->next;
	prev->next = item;
}

void insert(List*list, int entry)
{
		list->size++;
		if (!list->head) {
			insertNodeFront(list, createNode(entry, NULL));
			return;
	}
	
	Node *it = list->head;
	while (it->next) it = it->next;
	
	insertNodeMiddle(
		list,
		createNode(entry, NULL),
		it
	);	
}

void print(List* list)
{
	Node *it = list->head;
	while (it) {
		printf("%d ", it->data.entry);
		it = it->next;
	}
	printf("\n");
}

