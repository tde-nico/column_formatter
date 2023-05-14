#include "column_formatter.h"

/**
 * @brief a reverse version of strnchr (finds the first occourrence of the
 * character given as input)
 * @param s the string to search from
 * @param c the character to find
 * @param len the maximum length of the search
 * @return pointer to the first occourrence, if none found: NULL
 * 
 * a reverse implementation of strnchr (finds first char in string if possible)
 * that checks if the character is not a null-terminator and the given length
 * is used if greater than the input string length, finally it checks if the
 * character is found till the string first character
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
 * 
 * for every character in the input string, if the current character is a space
 * a counter is incremented, then it returns the total number of spaces
*/
size_t	count_spaces(char *s, size_t len)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0' && i < len)
	{
		if (s[i++] == ' ')
			++count;
	}
	return (count);
}

/**
 * @brief gets the length of an utf-8 character
 * @param c the character
 * @return character len if in utf-8, -1 if not
 * 
 * checks if a character is in utf-8 by testing with some and operations
 * the bytes for standard utf-8
*/
int	utf8_char_len(char c)
{
	if ((c & 0x80) == 0)
		return (1);
	if ((c & 0xE0) == 0xC0)
		return (2);
	if ((c & 0xF0) == 0xE0)
		return (3);
	if ((c & 0xF8) == 0xF0)
		return (4);
	return (-1);
}

/**
 * @brief evals the offset of utf-8 characters in a string
 * @param s the string to count from
 * @param len the maximum length of the count
 * @return the offset of the characters
 * 
 * for every character counts the offset generated by utf-8, by standard ascii
 * is one, so greater is consifìdered offset
*/
size_t	utf8_offset(char *s, size_t len)
{
	size_t	i;
	size_t	count;
	int		clen;

	i = 0;
	count = 0;
	while (s[i] != '\0' && i < (len + count))
	{
		clen = utf8_char_len(s[i]);
		if (clen == -1)
			return (-1);
		count += clen - 1;
		i += clen;
	}
	return (count);
}