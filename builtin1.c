#include "shell"

/**
 * _myhistory - displays the history list, one command by line, preceded with line numbers, starting at 0
 * @info: structure containg potential arguments. used to maintain constant function prototype
 * Return: always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);

}

/** 
 * unset_alias - sets alias to string
 * @info: parametr struct
 * @str: the string alias
 *
 * Return: always on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_inedex(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	 return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias 
 *
 * Return: always 0 on sucess , 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alais), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: alays 0 on sucess, 1 on error
 */

int print_alias(list_t *node)
{
	char *p = NULL, * = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_puchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (0);
}

/**
 * _myalias - minics the alias builtin (man alias)
 * @info: structure containg potential arguments. used to maintain constant function prototype
 *
 * Return: Always 0
 */

int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argv == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

