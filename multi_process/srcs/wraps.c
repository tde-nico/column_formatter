#include "column_formatter.h"

/**
 * @brief a pipeline wrapper for "retrive_data"
 * @param f the main formatter struct
 * @return 0 by default, if an error occours: 1
 * 
 * a simple "retrive_data" that afrer retriving the data, it sends them via
 * pipeline to the following process (format_data)
*/
int	retrive_data_wrapper(t_formatter *f)
{
	size_t	i;

	if (retrive_data(f))
		return (1);
	i = 0;
	while (f->cols.rows[i] != NULL)
	{
		if (f->cols.rows[i][0] != '\n')
		{
			write(STDOUT_FILENO, f->cols.rows[i], strlen(f->cols.rows[i]));
			if (f->cols.rows[i + 1] != NULL && f->cols.rows[i + 1][0] != '\0')
				write(STDOUT_FILENO, "\n", 1);
		}
		++i;
	}
	return (0);
}

/**
 * @brief a pipeline wrapper for "format_data"
 * @param f the main formatter struct
 * @return 0 by default, if an error occours: 1
 * 
 * a simple "format_data" that recives the retrived data from "retrive_data"
 * and after formatting the data, it sends them via pipeline to the following
 * process (save_data)
*/
int	format_data_wrapper(t_formatter *f)
{
	int	i;

	f->cols.rows = malloc(sizeof(char *));
	if (f->cols.rows == NULL)
		return (raise_error_i("malloc error", f));
	f->cols.rows[0] = NULL;
	i = -1;
	while ((++i > 0 && f->cols.rows[i - 1][0] != '\0') || i == 0)
	{
		f->cols.rows = realloc_matr(f->cols.rows, i + 2);
		if (f->cols.rows == NULL)
			return (raise_error_i("malloc error", f));
		f->cols.rows[i] = get_next_line(STDIN_FILENO, 1);
		if (f->cols.rows[i] == NULL)
			return (raise_error_i("malloc error", f));
	}
	if (format_data(f))
		return (1);
	i = -1;
	while (f->cols.cols[++i] != NULL)
	{
		write(STDOUT_FILENO, f->cols.cols[i], strlen(f->cols.cols[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * @brief a pipeline wrapper for "save_data"
 * @param f the main formatter struct
 * @return 0 by default, if an error occours: 1
 * 
 * a simple "save_data" that recives the formatted data from "format_data" to
 * save them to a file (and does some quick page separation)
*/
int	save_data_wrapper(t_formatter *f)
{
	size_t	i;

	f->cols.cols = malloc(sizeof(char *) * 2);
	if (f->cols.cols == NULL)
		return (raise_error_i("malloc error", f));
	f->cols.cols[1] = NULL;
	i = 0;
	while (1)
	{
		f->cols.cols[i] = get_next_line(STDIN_FILENO, 0);
		if (f->cols.cols[i] == NULL)
			return (raise_error_i("malloc error", f));
		if (f->cols.cols[i][0] == '\0')
			break ;
		f->cols.cols = realloc_matr(f->cols.cols, i + 3);
		if (f->cols.cols == NULL)
			return (raise_error_i("malloc error", f));
		++i;
	}
	if (save_data(f))
		return (1);
	return (0);
}
