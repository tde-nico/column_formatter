#include "column_formatter.h"

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

t_formatter	*raise_error_p(char *error, t_formatter *f)
{
	free_formatter(f);
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error, strlen(error));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

int	raise_error_i(char *error, t_formatter *f)
{
	free_formatter(f);
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error, strlen(error));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
