#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of pointers to the command-line arguments.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	int res;

	if (argc != 3)
	{
		dprintf(2, "Usage: %s filename text\n", argv[0]);
		exit(1);
	}

	res = create_file(argv[1], argv[2]);
	printf("-> %i)\n", res);

	return (0);
}
