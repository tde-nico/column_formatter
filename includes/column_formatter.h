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
	char	**form;
	char	**cols;
	char	**rows;
	int		curr;
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
	size_t		curr_char;
}	t_formatter;

// format.c
int			format_column(t_formatter *f, size_t len, int i);

// init.c
t_formatter	*init_formatter(char **args);

// save.c
int			save_columns(t_formatter *f);

// utils_formatter.c
void		free_formatter(t_formatter *f);
t_formatter	*raise_error_p(char *error, t_formatter *f);
int			raise_error_i(char *error, t_formatter *f);

// utils_string.c
char		*strnchr(char *s, char c, size_t len);
char		*rstrnchr(char *s, char c, size_t len);
int			count_spaces(char *s, size_t len);
int			utf8_char_len(char c);
int			utf8_offset(char *s, int len);

// utils.c
void		free_matrix(char **matrix);
char		*realloc_str(char *s, size_t size);
char		**realloc_matr(char **s, size_t size);
char		*get_next_line(int fd);

#endif
