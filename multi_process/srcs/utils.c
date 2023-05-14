#include "column_formatter.h"

/**
 * @brief free the bidimensional matrix given as input
 * @param matrix the matrix to be freed
 * 
 * loop on a matrix and free all the matrix allocated resources
*/
void	free_matrix(char **matrix)
{
	size_t	i;

	if (matrix == NULL)
		return ;
	i = 0;
	while (matrix[i] != NULL)
		free(matrix[i++]);
	free(matrix);
	matrix = NULL;
}

/**
 * @brief realloc a string to a new size (used to extend)
 * @param s the string to realloc
 * @param size the size of the realloc
 * @return the new allocated string
 * 
 * creates a new string with new size, then it copies the old content in the
 * new one, lastly it frees the old string and returns the new one (this
 * function is used to expand strings)
*/
char	*realloc_str(char *s, size_t size)
{
	char	*n;
	size_t	i;

	n = malloc(sizeof(char *) * size);
	if (n == NULL || s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < size)
	{
		n[i] = s[i];
		++i;
	}
	n[i] = '\0';
	while (i < size)
		n[i++] = '\0';
	free(s);
	return (n);
}

/**
 * @brief realloc a matrix to a new size (used to extend)
 * @param s the matrix to realloc
 * @param size the size of the realloc
 * @return the new allocated matrix
 * 
 * creates a new matrix with new size, then it copies the old content in the
 * new one, lastly it frees the old matrix and returns the new one (this
 * function is used to expand matrices)
*/
char	**realloc_matr(char **s, size_t size)
{
	char	**n;
	size_t	i;

	n = malloc(sizeof(char **) * size);
	if (n == NULL || s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != NULL && i < size)
	{
		n[i] = s[i];
		++i;
	}
	while (i < size)
		n[i++] = NULL;
	free(s);
	return (n);
}

/**
 * @brief reads a line by an fd replacing consecutive spaces with one
 * @param fd the file descriptor to read from
 * @return the line read by the fd (if possible)
 * 
 * allocates a buffer hat is used to store a line content read by an file
 * descriptor, and every time the string is reallocated with "realloc_str"
 * and every time encounters a spaces, tries to skip the following ones
*/
char	*get_monospaced_line(int fd)
{
	char	*buf;
	char	c;
	size_t	nbytes;
	int		i;

	buf = malloc(sizeof(char) * 2);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	buf[1] = '\0';
	c = '\0';
	nbytes = 1;
	i = -1;
	while (nbytes > 0)
	{
		if (i >= 0 && buf[i] == '\n')
			break ;
		nbytes = read(fd, &c, 1);
		if (i >= 0 && c == ' ' && buf[i] == ' ')
			continue ;
		buf[++i] = c;
		buf = realloc_str(buf, i + 3);
	}
	return (buf);
}

/**
 * @brief reads a line by an fd
 * @param fd the file descriptor to read from
 * @param newline if 0 -> no newline
 * @return the line read by the fd (if possible)
 * 
 * allocates a buffer hat is used to store a line content read by an file
 * descriptor, and every time the string is reallocated with "realloc_str"
*/
char	*get_next_line(int fd, int newline)
{
	char	*buf;
	size_t	nbytes;
	int		i;

	buf = malloc(sizeof(char) * 2);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	buf[1] = '\0';
	nbytes = 1;
	i = -1;
	while (nbytes > 0)
	{
		if (i >= 0 && buf[i] == '\n')
		{
			if (newline == 0)
				buf[i] = '\0';
			break ;
		}
		nbytes = read(fd, &buf[++i], 1);
		buf = realloc_str(buf, i + 3);
	}
	return (buf);
}
