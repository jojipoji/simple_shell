#include "shell.h"

/**
 *  _strlen - returns length of a string
 * @str: string to be evaluated
 *
 * Return: the length of the string
 */
int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);

	while (*str != '\0')
	{
		i++;
		str++;
	}

	return (i);
}

/**
 * _strdup - allocates a space in memory for a copy of a string
 * @src: string a copy is made of
 *
 * Return: a pointer to the copy, or NULL if failure
 */
char *_strdup(char *src)
{
	int len = _strlen(src);
	char *dest = malloc(len + 1);
	char *ptr;

	if (dest == NULL)
		exit(EXIT_FAILURE);

	ptr = dest;

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}

/**
 * str_concat - concatenates two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: a pointer to the new string, or NULL if failure
 */
char *str_concat(char *s1, char *s2)
{
	int len = _strlen(s1) + _strlen(s2);
	char *dest = malloc(len + 1);
	char *ptr = dest;

	if (s1 != NULL)
	{
		while (*s1 != '\0')
		{
			*ptr = *s1;
			ptr++;
			s1++;
		}
	}

	if (s2 != NULL)
	{
		while (*s2 != '\0')
		{
			*ptr = *s2;
			ptr++;
			s2++;
		}
	}

	*ptr = '\0';

	return (dest);
}

/**
 * str_compare - compare two string
 * @s1: string to be compared
 * @s2: string to be compared
 * @pref_or_match: if string needs to be matched exactly or if just a prefix
 * needs to be matched
 *
 * Return: difference between strings
 */
int str_compare(char *s1, char *s2, int pref_or_match)
{
	if (s1 == NULL || s2 == NULL)
		return (FALSE);

	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (FALSE);

		s1++;
		s2++;
	}

	if (pref_or_match == PREFIX)
		return (TRUE);

	if (*s1 == *s2)
		return (TRUE);

	return (FALSE);
}
