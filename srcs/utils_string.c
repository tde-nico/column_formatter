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
