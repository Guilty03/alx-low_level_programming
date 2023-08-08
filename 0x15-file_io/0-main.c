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
	ssize_t n;

	if (argc != 2)
	{
		dprintf(2, "Usage: %s filename\n", argv[0]);
		exit(1);
	}

	n = read_textfile(argv[1], 114);
	printf("\n(printed chars: %li)\n", n);

	n = read_textfile(argv[1], 1024);
	printf("\n(printed chars: %li)\n", n);

	return (0);
}
