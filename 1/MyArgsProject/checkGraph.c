/*
*       COMP340 - Operating Systems
*       Assignment 1
*       Group 2
*       Alp Deniz Senyurt - 300203734 & Mithun Krishnaprasad 300184390
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


typedef struct
{
	char *letters;
} word;

void createNode(word *wordAddress, char const *arg, size_t argSize)
{
	wordAddress->letters = malloc(argSize);
	for (int i = 0; i < strlen(arg); ++i)
	{
		wordAddress->letters[i] = arg[i];
	}
}

void deleteNode(word *wordAddress, size_t index)
{
	free((wordAddress+index)->letters);
}

int main(int argc, char const *argv[])
{
	printf("Welcome to CheckGraph Program. Initializing...\n");
	if (argc > 3)
	{
		printf("Please only write maximum of 2 arguments as more than 2 is not supported yet.");
		return EXIT_FAILURE;
	}

	if (!((strcmp(argv[1], "sorted") || strmp(argv[1], "size")) && (strcmp(argv[2], "sorted") || strcmp(argv[2], "size"))))
	{
		printf("Wrong parameter or argument passed, please execute with correct arguments");
		return EXIT_FAILURE;
	}

	word _argArr[argc-1];

	for (int i = 0; i < argc-1; ++i)
	{
		createNode(&(_argArr[i]), argv[i+1], sizeof(char) * strlen(argv[i+1]));
	}

	int pid;

	char *program;
	char *const (*_argv) = NULL;
	if (! strcmp(argv[1], "sorted"))
	{
		program = "./FIRST_PROGRAM";
	}
	else if (! strcmp(argv[1], "size"))
	{
		program = "./SEC_PROGRAM";
	}
	if ((pid = fork()) != 0)
	{
		int status = 0;
		if (-1 == waitpid(pid, &status, 0))
		{
			printf("Did not successfully create child process.\n");
		}
		else
		{
			printf("Finished waiting for child to execute with low-order bits exit status %d.\n", WEXITSTATUS(status));
		}
	}
	else
	{
		execv(program, argv);
		exit(0);
	}
	if (argc == 3)
	{
		if (! strcmp(argv[2], "sorted"))
		{
			program = "./FIRST_PROGRAM";
		}
		else if (! strcmp(argv[2], "size"))
		{
			program = "./SEC_PROGRAM";
		}
		if ((pid = fork()) != 0)
		{
			int status = 0;
			if (-1 == waitpid(pid, &status, 0))
			{
				printf("Did not successfully create child process.\n");
			}
			else
			{
				printf("Finished waiting for child to execute with low-order bits exit status %d.\n", WEXITSTATUS(status));
			}
		}
		else
		{
			execv(program, argv);
			exit(0);
		}
	}
	return EXIT_SUCCESS;
}