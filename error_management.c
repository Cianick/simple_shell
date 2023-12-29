#include "shell.h"

/**
 * errorAtoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in the string, converted number otherwise.
 *         -1 on error.
 */
int errorAtoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printErrorMessage - Prints an error message.
 * @info: The parameter and return info struct.
 * @errorString: String containing specified error type.
 *
 * Return: Nothing.
 */
void printErrorMessage(info_t *info, char *errorString)
{
	_eputs(info->fname);
	_eputs(": ");
	printDecimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(errorString);
}

/**
 * printDecimal - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int printDecimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absoluteValue, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		absoluteValue = -input;
		__putchar('-');
		count++;
	}
	else
		absoluteValue = input;
	current = absoluteValue;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absoluteValue / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertNumber - Converter function, a clone of itoa.
 * @num: The number.
 * @base: The base.
 * @flags: Argument flags.
 *
 * Return: The string representation of the number.
 */
char *convertNumber(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removeComments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: Always 0.
 */
void removeComments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

