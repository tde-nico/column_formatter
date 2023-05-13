#include "column_formatter.h"

/**
 * @brief free the bidimensional matrix given as input
 * @param matrix the matrix to be freed
*/
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

/**
 * @brief realloc a string to a new size (used to extend)
 * @param s the string to realloc
 * @param size the size of the realloc
 * @return the new allocated string
*/
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

/**
 * @brief realloc a matrix to a new size (used to extend)
 * @param s the matrix to realloc
 * @param size the size of the realloc
 * @return the new allocated matrix
*/
char	**realloc_matr(char **s, size_t size)
{
	char	**n;
	size_t	i;

	n = malloc(sizeof(char **) * size);
	if (n == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != NULL && i < size)
		n[i] = s[i];
	while (i < size)
		n[i++] = NULL;
	free(s);
	return (n);
}

/**
 * @brief reads a line by an fd
 * @param fd the file descriptor to read from
 * @return the line read by the fd (if possible)
*/
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
