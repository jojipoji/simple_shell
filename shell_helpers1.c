#include "shell.h"

int status;

int line_num;

char *shell_name;

/**
 * input_san - sanitizes input from the command line
 * @old_buf: buffer to be sanitized
 * @old_size: size of old buffer
 *
 * Return: the new, sanitized buffer
 */
char *input_san(char *old_buf, size_t *old_size)
{
	char *new_buf = malloc(*old_size * 3);
	char *new_ptr = new_buf;
	char *old_ptr = old_buf;

	while (*old_ptr != '\0')
	{
		while (*old_ptr == ' ')
			old_ptr++;
		while (*old_ptr	!= ' ' && *old_ptr != ';' && *old_ptr != '|'
		       && *old_ptr != '&' && *old_ptr != '\0')
		{
			*new_ptr = *old_ptr;
			new_ptr++;
			old_ptr++;
		}
		while (*old_ptr == ' ')
			old_ptr++;
		if (new_ptr != new_buf && *old_ptr != '\0')
		{
			*new_ptr = ' ';
			new_ptr++;
		}

		if (*old_ptr == ';' || *old_ptr == '|' || *old_ptr == '&')
		{
			if (input_err_check(old_ptr) == FALSE)
			{
				*old_size = 0;
				break;
			}
			*new_ptr = *old_ptr;
			if (*old_ptr == ';')
			{
				new_ptr++;
				*new_ptr = ' ';
			}
			else if (*(old_ptr + 1) == *old_ptr)
			{
				if (new_ptr == new_buf)
				{
					err_message(old_ptr, NULL);
					*old_size = 0;
					break;
				}
				new_ptr++;
				*new_ptr = *old_ptr;
				new_ptr++;
				*new_ptr = ' ';
				old_ptr++;
			}
			new_ptr++;
			old_ptr++;
		}
	}
	*new_ptr = '\0';
	free(old_buf);
	return (new_buf);
}

/**
 * input_err_check - helper function for sanitizer, check for unexpected char
 * @ptr: pointer to area that needs to be checked
 *
 * Return: TRUE if no error, FALSE if error
 */
int input_err_check(char *ptr)
{
	char *iter = ptr;

	iter++;
	if (*ptr == ';' && *iter == *ptr)
	{
		err_message(ptr, NULL);
		return (FALSE);
	}
	if (*iter == *ptr)
		iter++;

	while (*iter == ' ')
		iter++;

	if (*iter == ';' || *iter == '|' || *iter == '&')
	{
		err_message(iter, NULL);
		return (FALSE);
	}

	return (TRUE);
}

/**
 * err_message - prints error messages and sets status
 * @arg0: command that is causing error
 * @arg1: first argument to command
 */
void err_message(char *arg0, char *arg1)
{
	char *err_str_num = _itoa(line_num);

	write(STDERR_FILENO, shell_name, _strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_str_num, _strlen(err_str_num));
	free(err_str_num);

	if (str_compare("cd", arg0, MATCH) == TRUE)
	{
		status = 2;
		write(STDERR_FILENO, ": cd: can't cd to", 17);
		write(STDERR_FILENO, arg1, _strlen(arg1));
		write(STDERR_FILENO, "\n", 1);
		return;
	}

	if (str_compare("exit", arg0, MATCH) == TRUE)
	{
		write(STDERR_FILENO, ": exit: Illegal number: ", 24);
		write(STDERR_FILENO, arg1, _strlen(arg1));
		write(STDERR_FILENO, "\n", 1);
		return;
	}
	if (*arg0 == ';' || *arg0 == '|' || *arg0 == '&')
	{
		status = 2;
		write(STDERR_FILENO, ": Syntax error: \"", 17);
		write(STDERR_FILENO, arg0, 1);
		if (*arg0 == *(arg0 + 1))
			write(STDERR_FILENO, arg0, 1);
		write(STDERR_FILENO, "\" unexpected\n", 14);
		return;
	}

	status = 127;
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arg0, _strlen(arg0));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * check_for_vars - checks an argument to see if it is a variable and if so,
 * replaces it with it's value
 * @arg: argument to be checked
 *
 * Return: a pointer to the evaluated argument (either new or an altered clone)
 */
char *check_for_vars(char *arg)
{
	char *clone = NULL;
	char *ptr = arg;
	char *next;
	char *tmp;
	int is_var;
	int i;

	while (*ptr != '\0')
	{
		if (*ptr == '$')
		{
			if (clone == NULL)
			{
				clone = _strdup(arg);
				i = ptr - arg;
				ptr = clone + i;
			}
			next = ptr + 1;
			while (*next != '\0' && *next != '$' && *next != '#')
				next++;
			if (*next == '$' && next > ptr + 1)
				is_var = TRUE;
			else if (*next == '#')
				is_var = NEITHER;
			else
				is_var = FALSE;

			*next = '\0';

			if (str_compare("$?", ptr, MATCH) == TRUE)
				tmp = _itoa(status);
			else if (str_compare("$0", ptr, MATCH) == TRUE)
				tmp = _strdup(shell_name);
			else if (get_array_element(environ, ptr + 1) != NULL)
				tmp = _strdup(get_array_element
					      (environ, ptr + 1)
					      + _strlen(ptr));
			else
				tmp = _strdup("");

			*ptr = '\0';
			ptr = str_concat(clone, tmp);
			free(tmp);
			if (is_var == FALSE)
			{
				free(clone);
				clone = ptr;
				break;
			}
			if (is_var == TRUE)
				*next = '$';
			else if (is_var == NEITHER)
				*next = '#';
			tmp = str_concat(ptr, next);
			free(ptr);
			ptr = tmp;
			free(clone);
			clone = ptr;
			if (is_var == NEITHER)
			{
				while (*ptr != '#')
					ptr++;
			}
		}
		ptr++;
	}
	if (clone != NULL)
		return (clone);

	return (arg);
}
