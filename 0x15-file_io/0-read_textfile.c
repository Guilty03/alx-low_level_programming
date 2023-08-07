#include "main.h"
#include <stdlib.h>

/**
 * read_textfile- Read text file print to STDOUT.
 * @filename:text file being read
 * @letters: number of letters to  be read
 * Return: w- actual number of bytes read and printed
 * 0 when function fauls or filename is NULL
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buf;
	ssize_t fd;
	sszie_t w;
	ssize_t t;

	fd = open(filename, IO_RDONLY);
	if (fd == -1)
		return (0);
	`buf = malloc(sizeof(char) *oletters);
	t = read(fd, buf, letters);
	w = write(STDOUT_FILENO, buf, t);

	free(buf);
	close(fd);
	return (w);
}
