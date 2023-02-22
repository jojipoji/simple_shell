#include "shell.h"

int status;

/**
 * free_aliases - frees all aliases
 * @alias_ptr: ptr to head of alias list
 *
 * Return: TRUE
 */
int free_aliases(alias *alias_ptr)
{
	alias *tmp;

	while (alias_ptr != NULL)
	{
		tmp = alias_ptr;
		alias_ptr = alias_ptr->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}

	return (TRUE);
}

/**
 * check_if_alias - if the alias command is not called, this will check if the
 * command is an alias, and if so replace it with it's value
 * @args: argument to be checked
 * @alias_ptr: points to list of aliases to be checked against
 *
 * Return: TRUE
 */
int check_if_alias(char **args, alias *alias_ptr)
{
	while (alias_ptr != NULL)
	{
		if (str_compare(*args, alias_ptr->name, MATCH) == TRUE)
		{
			*args = _strdup(alias_ptr->value);
			return (DO_EXECVE);
		}
		alias_ptr = alias_ptr->next;
	}
	return (TRUE);
}

/**
 * print_aliases - prints all aliases in list
 * @alias_ptr: points to list of aliases
 *
 * Return: SKIP_FORK
 */
int print_aliases(alias *alias_ptr)
{
	while (alias_ptr != NULL)
	{
		write(STDOUT_FILENO, alias_ptr->name, _strlen(alias_ptr->name));
		write(STDOUT_FILENO, "=\'", 2);
		write(STDOUT_FILENO, alias_ptr->value,
		      _strlen(alias_ptr->value));
		write(STDOUT_FILENO, "\'\n", 2);
		alias_ptr = alias_ptr->next;
	}
	return (SKIP_FORK);
}

/**
 * print_alias_value - prints the value of a particular alias
 * @arg: name of alias
 * @alias_ptr: points to list of aliases
 *
 * Return: TRUE if valid alias, FALSE if not
 */
int print_alias_value(char *arg, alias *alias_ptr)
{
	while (alias_ptr != NULL)
	{
		fflush(stdin);
		if (str_compare(arg, alias_ptr->name, MATCH) == TRUE)
		{
			write(STDOUT_FILENO, arg, _strlen(arg));
			write(STDOUT_FILENO, "=\'", 2);
			write(STDOUT_FILENO, alias_ptr->value,
			      _strlen(alias_ptr->value));
			write(STDOUT_FILENO, "\'\n", 2);
			return (TRUE);
		}
		alias_ptr = alias_ptr->next;
	}

	status = 1;
	write(STDERR_FILENO, "alias: ", 7);
	write(STDERR_FILENO, arg, _strlen(arg));
	write(STDERR_FILENO, " not found\n", 11);

	return (FALSE);
}

/**
 * set_alias_value - initializes an alias or resets its value if it exists
 * @arg: name of alias
 * @alias_ptr: pointer to list of aliases
 * @new_value: value of alias to be set
 *
 * Return: TRUE
 */
int set_alias_value(char *arg, alias *alias_ptr, char *new_value)
{
	while (alias_ptr->next != NULL
	       && str_compare(alias_ptr->name, arg, MATCH) != TRUE)
	{
		alias_ptr = alias_ptr->next;
	}

	if (str_compare(alias_ptr->name, arg, MATCH) == TRUE)
	{
		free(alias_ptr->value);
	}
	else
	{
		alias_ptr->next = malloc(sizeof(alias *));
		alias_ptr = alias_ptr->next;
		if (alias_ptr == NULL)
			exit(EXIT_FAILURE);

		alias_ptr->name = _strdup(arg);
		alias_ptr->next = NULL;
	}
	alias_ptr->value = _strdup(new_value);

	return (TRUE);
}
