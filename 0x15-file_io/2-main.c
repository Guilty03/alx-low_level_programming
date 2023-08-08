#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of pointers to the command-line arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char **argv)
{
	int res;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s filename text\n", argv[0]);
		return (1);
	}

	res = append_text_to_file(argv[1], argv[2]);
	if (res == -1)
	{
		perror("Error appending text to file");
		return (1);
	}

	printf("Text appended successfully.\n");
	return (0);
}
