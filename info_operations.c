#include "shell.h"

/**
 * clearInfo - Initializes info_t struct.
 * @info: Struct address.
 */
void clearInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - Initializes info_t struct.
 * @info: Struct address.
 * @av: Argument vector.
 */
void setInfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAlias(info);
		replaceVars(info);
	}
}

/**
 * freeInfo - Frees info_t struct fields.
 * @info: Struct address.
 * @all: True if freeing all fields.
 */
void freeInfo(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

