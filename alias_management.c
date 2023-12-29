#include "shell.h"

/**
 * displayHistory - Displays the history list, one command per line,
 *                  preceded with line numbers starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int displayHistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unsetAlias - Unsets an alias by deleting it from the alias list.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unsetAlias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, nodeStartsWith(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setAlias - Sets an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int setAlias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printAlias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int printAlias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manageAlias - Manages aliases, displaying or setting them.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int manageAlias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			setAlias(info, info->argv[i]);
		else
			printAlias(nodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}

