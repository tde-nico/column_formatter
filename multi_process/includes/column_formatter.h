#ifndef COLUMN_FORMATTER_H
# define COLUMN_FORMATTER_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <sys/wait.h>

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
	char	**rows;
	char	**cols;
	char	**form;
	size_t	curr;
}	t_columns;

/**
 * @brief the main struct of the program used to store attributes of the
 * output data, the input and output files descriptors and various buffers
*/
typedef struct s_formatter
{
	size_t		max;
	size_t		width;
	size_t		height;
	size_t		dist;
	int			in_fd;
	int			out_fd;
	t_columns	cols;
	size_t		curr_char;
}	t_formatter;

// data.c
int			retrive_data(t_formatter *f);
int			format_data(t_formatter *f);
int			save_data(t_formatter *f);

// format.c
int			format_column(t_formatter *f, size_t len, size_t i);

// init.c
t_formatter	*init_formatter(char **args);

// pipeline.c
int			pipeline(t_formatter *f);

// save.c
int			save_columns(t_formatter *f);

// utils_formatter.c
void		free_formatter(t_formatter *f);
t_formatter	*raise_error_p(char *error, t_formatter *f);
int			raise_error_i(char *error, t_formatter *f);

// utils_string.c
char		*rstrnchr(char *s, char c, size_t len);
size_t		count_spaces(char *s, size_t len);
size_t		utf8_offset(char *s, size_t len);

// utils.c
void		free_matrix(char **matrix);
char		*realloc_str(char *s, size_t size);
char		**realloc_matr(char **s, size_t size);
char		*get_monospaced_line(int fd);
char		*get_next_line(int fd, int newline);

// wraps.c
int			retrive_data_wrapper(t_formatter *f);
int			format_data_wrapper(t_formatter *f);
int			save_data_wrapper(t_formatter *f);

#endif
