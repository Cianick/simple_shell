#include "shell.h"

/**
 * printErrorString - Prints an input string to standard error.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void printErrorString(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		writeErrorCharacter(str[i]);
		i++;
	}
}

/**
 * writeErrorCharacter - Writes the character c to standard error.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeErrorCharacter(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * writeCharacterToFileDescriptor - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeCharacterToFileDescriptor(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * writeStringToFileDescriptor - Writes an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int writeStringToFileDescriptor(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += writeCharacterToFileDescriptor(*str++, fd);
	}
	return (i);
}

