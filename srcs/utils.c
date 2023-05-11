#include "column_formatter.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (matrix == NULL)
		return ;
	i = -1;
	while (matrix[++i] != NULL)
		free(matrix[i]);
	free(matrix);
}

char	*realloc_str(char *s, size_t size)
{
	char	*n;
	size_t	i;

	n = malloc(sizeof(char *) * size);
	if (n == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		n[i] = s[i];
	n[i] = '\0';
	free(s);
	return (n);
}

char	**realloc_matr(char **s, size_t size)
{
	char	**n;
	size_t	i;

	n = malloc(sizeof(char **) * size);
	if (n == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != NULL)
		n[i] = s[i];
	n[i] = NULL;
	free(s);
	return (n);
}

char	*get_next_line(int fd)
{
	char	*buf;
	int		nbytes;
	int		i;

	buf = malloc(sizeof(char) * 1);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	nbytes = 1;
	i = -1;
	while (nbytes > 0)
	{
		if (buf[i] == '\n')
			break ;
		nbytes = read(fd, &buf[++i], 1);
		buf = realloc_str(buf, i + 2);
		buf[i + 1] = '\0';
	}
	return (buf);
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
