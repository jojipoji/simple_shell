#include "shell.h"

/**
 * _itoa - converts an int into a string
 * @n: int to be converted
 *
 * Return: the converted number
 */
char *_itoa(int n)
{
	char *buf = malloc(12);
	char *ptr = buf;
	int is_min = FALSE;
	int i_mask = 1000000000;
	int digit = 0;

	if (n == INT_MIN)
	{
		*ptr = '-';
		ptr++;
		n = INT_MAX;
		is_min = TRUE;
	}

	if (n < 0)
	{
		*ptr = '-';
		ptr++;
		n = -n;
	}

	while (i_mask > 9 && digit == 0)
	{
		digit = n / i_mask;
		n %= i_mask;
		i_mask /= 10;
	}

	if (digit != 0)
	{
		*ptr = digit + '0';
		ptr++;
	}

	while (i_mask > 9)
	{
		digit = n / i_mask;
		*ptr = digit + '0';
		ptr++;
		n %= i_mask;
		i_mask /= 10;
	}

	if (is_min == TRUE)
		n += 1;

	*ptr = n + '0';
	ptr++;
	*ptr = '\0';
	return (buf);
}

/**
 * _atoi - converts a string into a number
 * @s: string to be converted
 *
 * Return: the converted number
 */
int _atoi(char *s)
{
	int n = 0;
	int sign = 1;
	int s_int;

	if (*s == '=' && *(s + 1) >= '0' && *(s + 1) <= '9')
	{
		sign = -1;
		s++;
	}

	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
		{
			s_int = *s - 48;
			if (sign == 1)
				n = (n * 10) + s_int;
			else
				n = (n * 10) - s_int;
		}
		else
			return (-1);
		s++;
	}

	return (n);
}
