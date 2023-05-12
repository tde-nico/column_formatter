#include "column_formatter.h"

char	*strnchr(char *s, char c, size_t len)
{
	size_t	i;

	if (c == '\0')
		return (s);
	i = -1;
	while (s[++i] != '\0' && i < len)
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (NULL);
}

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
