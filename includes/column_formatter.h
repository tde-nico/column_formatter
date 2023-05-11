#ifndef COLUMN_FORMATTER_H
# define COLUMN_FORMATTER_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <sys/mman.h>
# include <sys/stat.h>

# include <stdio.h>

# define DEBUG 1

typedef struct s_columns
{
	char			**form;
	char			**cols;
	char			**rows;
}	t_columns;

typedef struct s_formatter
{
	int			max;
	int			width;
	int			height;
	int			dist;
	int			in_fd;
	int			in_size;
	int			out_fd;
	t_columns	cols;
}	t_formatter;

// init.c
t_formatter	*init_formatter(char **args);

// utils.c
void		free_matrix(char **matrix);
char		*realloc_str(char *s, size_t size);
char		**realloc_matr(char **s, size_t size);
char		*get_next_line(int fd);
char		*rstrnchr(char *s, char c, size_t len);
char		*strnchr(char *s, char c, size_t len);

// utils_formatter.c
void		free_formatter(t_formatter *f);
t_formatter	*raise_error_p(char *error, t_formatter *f);
int			raise_error_i(char *error, t_formatter *f);

#endif
