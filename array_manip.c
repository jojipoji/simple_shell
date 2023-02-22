#include "shell.h"

/**
 * get_array_element - gets an element of an array
 * @array: array to be searched
 * @element_name: name of element to be found
 *
 * Return: the array element, or NULL if it is not found
 */
char *get_array_element(char **array, char *element_name)
{
	while (*array != NULL)
	{
		if (str_compare(*array, element_name, PREFIX) == TRUE)
			return (*array);

		array++;
	}

	return (NULL);
}

/**
 * make_array - makes a list from a buffer
 * @str: the buffer
 * @delim: character to mark the end of a list entry
 * @if_sep: if the string has semicolons, if_sep becomes the location after the
 * semicolon
 *
 * Return: a pointer to the list
 */
char **make_array(char *str, char delim, char **if_sep)
{
	char *str_ptr = str;
	unsigned int i = 2;
	char **array = NULL;

	while (*str_ptr != '\0')
	{
		if (*str_ptr == ';')
			break;
		if (*str_ptr == delim && *(str_ptr + 1) != '\0')
			i++;

		str_ptr++;
	}

	array = malloc(i * sizeof(char **));
	if (array == NULL)
		exit(EXIT_FAILURE);

	array[0] = str;
	str_ptr = str;
	i = 1;

	while (*str_ptr != '\0')
	{
		if (*str_ptr == delim)
		{
			*str_ptr = '\0';
			str_ptr++;
			if (*str_ptr == ';')
			{
				array[i] = NULL;
				if (*(str_ptr + 1) != '\0' && *(str_ptr + 2) != '\0')
					*if_sep = str_ptr + 2;
				break;
			}
			if (*str_ptr != '\0')
			{
				array[i] = str_ptr;
				i++;
			}
		}
		str_ptr++;
	}
	array[i] = NULL;

	return (array);
}

/**
 * list_len - finds the length of a list, or the index of an entry
 * @list: list to be evaluated
 * @entry: entry to be indexed
 *
 * Return: length or index if success, -1 if failure
 */
int list_len(char **list, char *entry)
{
	int i = 0;

	if (entry == NULL)
	{
		while (*list != NULL)
		{
			i++;
			list++;
		}
		i++;
		return (i);
	}
	else
	{
		while (*list != NULL)
		{
			if (str_compare(*list, entry, PREFIX) == TRUE)
				return (i);

			i++;
			list++;
		}
	}

	return (-1);
}

/**
 * array_cpy - copies an array
 * @old_array: array to be copied
 * @new_size: size of new array
 *
 * Return: the new array
 */
char **array_cpy(char **old_array, int new_size)
{
	char **new_array = NULL;
	char **ptr_array;

	new_array = malloc(sizeof(char **) * new_size);

	ptr_array = new_array;
	while (*old_array != NULL)
	{
		*ptr_array = _strdup(*old_array);
		ptr_array++;
		old_array++;
	}
	*ptr_array = NULL;

	return (new_array);
}

/**
 * free_array - frees a two dimensional array
 * @args: array to be freed
 *
 * Return: TRUE
 */
int free_array(char **args)
{
	char **ptr = args;

	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}

	free(args);

	return (TRUE);
}
