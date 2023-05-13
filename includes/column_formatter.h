#ifndef COLUMN_FORMATTER_H
# define COLUMN_FORMATTER_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>

/**
 * @brief every page generated will be separated by this string
*/
# define PAGE_SEPARATOR "\n %%% \n"

/**
 * @brief a struct used to store all the columns strings, from the non
 * formatted to the finished ones
*/
typedef struct s_columns
{
	char	**form;
	char	**cols;
	char	**rows;
	int		curr;
}	t_columns;

/**
 * @brief the main struct of the program used to store attributes of the
 * output data, the input and output files descriptors and various buffers
*/
typedef struct s_formatter
{
	int			max;
	int			width;
	int			height;
	int			dist;
	int			in_fd;
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
