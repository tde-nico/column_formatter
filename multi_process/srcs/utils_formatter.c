#include "column_formatter.h"

/**
 * @brief free all the allocated resources into the formatter main structure
 * @param f the main formatter struct
 * 
 * frees all the allocated resources into the formatter struct and closes the
 * open files
*/
void	free_formatter(t_formatter *f)
{
	if (f == NULL)
		return ;
	if (f->in_fd != STDIN_FILENO)
		close(f->in_fd);
	if (f->out_fd != STDOUT_FILENO)
		close(f->out_fd);
	if (f->cols.rows != NULL)
		free_matrix(f->cols.rows);
	if (f->cols.cols != NULL)
		free_matrix(f->cols.cols);
	if (f->cols.form != NULL)
		free_matrix(f->cols.form);
	free(f);
}

/**
 * @brief writes on stderr (2) an error after freeing the resources
 * @param error the string containing the error's descripton
 * @param f the main formatter struct
 * @return NULL representing an error
 * 
 * after freeing all the formatter resources, writes an error on stderr (2)
 * and returns NULL (needed for some allocation functions) like an error
*/
t_formatter	*raise_error_p(char *error, t_formatter *f)
{
	free_formatter(f);
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error, strlen(error));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

/**
 * @brief writes on stderr (2) an error after freeing the resources
 * @param error the string containing the error's descripton
 * @param f the main formatter struct
 * @return 1 representing an error
 * 
 * after freeing all the formatter resources, writes an error on stderr (2)
 * and returns 1 like an error
*/
int	raise_error_i(char *error, t_formatter *f)
{
	free_formatter(f);
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error, strlen(error));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
