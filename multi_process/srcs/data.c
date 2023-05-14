#include "column_formatter.h"

/**
 * @brief this function reads the data taken as input line by line and storing
 * it in a buffer of rows
 * @param f the formatter structure
 * @return 0 by default, if an error occours: 1
 * 
 * It starts by initializing the 2D matrix to store the read data, if it fails,
 * will return error, then it calls "get_next_line" to retrve a line from the
 * input file also checking if it is the last line ('\0' of first char)
 * that means that the input file is finished (EOF), lastly it realloc the
 * matrix for further lines (this process of reading and storing data is done
 * untill EOF)
*/
int	retrive_data(t_formatter *f)
{
	size_t	i;

	f->cols.rows = malloc(sizeof(char *) * 2);
	if (f->cols.rows == NULL)
		return (raise_error_i("malloc error", f));
	f->cols.rows[1] = NULL;
	i = 0;
	while (1)
	{
		f->cols.rows[i] = get_monospaced_line(f->in_fd);
		if (f->cols.rows[i] == NULL)
			return (raise_error_i("malloc error", f));
		if (f->cols.rows[i][0] == '\0')
			break ;
		f->cols.rows = realloc_matr(f->cols.rows, i + 3);
		if (f->cols.rows == NULL)
			return (raise_error_i("malloc error", f));
		++i;
	}
	if (f->in_fd != STDIN_FILENO)
		close(f->in_fd);
	f->in_fd = STDIN_FILENO;
	return (0);
}

/**
 * @brief this function formats data from the source to a column format
 * @param f the formatter structure
 * @return 0 by default, if an error occours: 1
 * 
 * After initializing the matrix used to store the formatted data it
 * loops on the previously retrived data formatting line by line
*/
int	format_data(t_formatter *f)
{
	size_t	len;
	size_t	i;

	f->cols.cols = malloc(sizeof(char *) * 2);
	if (f->cols.cols == NULL)
		return (raise_error_i("malloc error", f));
	f->cols.cols[0] = NULL;
	i = 0;
	while (f->cols.rows[i] != NULL)
	{
		f->curr_char = 0;
		len = strlen(f->cols.rows[i]);
		if (format_column(f, len, i))
			return (1);
		++i;
	}
	return (0);
}

/**
 * @brief this function saves the data previously formatted by dividing into
 * pages and writing down in the output the result
 * @param f the formatter structure
 * @return 0 by default, if an error occours: 1
 * 
 * the formatted data is splitted into pages and writed to the output file
*/
int	save_data(t_formatter *f)
{
	size_t	i;

	if (save_columns(f))
		return (1);
	i = 0;
	while (f->cols.form[i] != NULL)
	{
		write(f->out_fd, f->cols.form[i], strlen(f->cols.form[i]));
		write(f->out_fd, "\n", 1);
		++i;
	}
	if (f->out_fd != STDOUT_FILENO)
		close(f->out_fd);
	f->out_fd = STDOUT_FILENO;
	return (0);
}
