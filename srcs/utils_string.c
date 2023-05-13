#include "column_formatter.h"

/**
 * @brief a reverse version of strnchr (finds the first occourrence of the
 * character given as input)
 * @param s the string to search from
 * @param c the character to find
 * @param len the maximum length of the search
 * @return pointer to the first occourrence, if none found: NULL
*/
char	*rstrnchr(char *s, char c, size_t len)
{
	size_t	i;

	if (c == '\0')
		return (s);
	if (len > strlen(s))
		i = strlen(s);
	else
		i = len;
	while (i > 0)
	{
		if (s[i - 1] == c)
			return (&s[i - 1]);
		--i;
	}
	return (NULL);
}

/**
 * @brief counts the spaces in a string
 * @param s the string to count from
 * @param len the maximum length of the count
 * @return number of spaces
*/
int	count_spaces(char *s, size_t len)
{
	int		count;
	size_t	i;

	count = 0;
	i = -1;
	while (s[++i] != '\0' && i < len)
	{
		if (s[i] == ' ')
			++count;
	}
	return (count);
}

/**
 * @brief gets the length of an utf-8 character
 * @param c the character
 * @return character len if in utf-8, -1 if not
*/
int	utf8_char_len(char c)
{
	if ((c & 0x80) == 0)
		return (1);
	else if ((c & 0xE0) == 0xC0)
		return (2);
	else if ((c & 0xF0) == 0xE0)
		return (3);
	else if ((c & 0xF8) == 0xF0)
		return (4);
	return (-1);
}

/**
 * @brief evals the offset of utf-8 characters in a string
 * @param s the string to count from
 * @param len the maximum length of the count
 * @return the offset of the characters
*/
int	utf8_offset(char *s, int len)
{
	int	i;
	int	clen;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && i < (len + count))
	{
		clen = utf8_char_len(s[i]);
		if (clen == -1)
			return (-1);
		count += clen - 1;
		i += clen;
	}
	return (count);
}
