#include "column_formatter.h"

int	usage(char *name)
{
	write(STDOUT_FILENO, "Usage: ", 7);
	write(STDOUT_FILENO, name, strlen(name));
	write(STDOUT_FILENO, " columns_per_page columns_height columns_width", 46);
	write(STDOUT_FILENO, " columns_distance [in_file] [out_file]\n", 39);
	return (1);
}

int	retrive_data(t_formatter *f)
{
	int	i;

	i = -1;
	f->cols.rows = malloc(sizeof(char *) * 2);
	if (f->cols.rows == NULL)
		return (raise_error_i("malloc error", f));
	f->cols.rows[1] = NULL;
	while (1)
	{
		f->cols.rows[++i] = get_next_line(f->in_fd);
		if (f->cols.rows[i] == NULL)
			return (raise_error_i("malloc error", f));
		if (f->cols.rows[i][0] == '\0')
			break ;
		f->cols.rows = realloc_matr(f->cols.rows, i + 3);
		f->cols.rows[i + 2] = NULL;
	}
	return (0);
}

int	format_data(t_formatter *f)
{
	size_t	len;
	int		i;

	i = -1;
	f->cols.cols = malloc(sizeof(char *) * 2);
	if (f->cols.cols == NULL)
		return (raise_error_i("malloc error", f));
	f->cols.cols[1] = NULL;
	while (f->cols.rows[++i] != NULL)
	{
		f->curr_char = 0;
		len = strlen(f->cols.rows[i]);
		if (format_column(f, len, i))
			return (1);
	}
	return (0);
}

int	save_data(t_formatter *f)
{
	unsigned int	i;

	if (save_columns(f))
		return (1);
	i = -1;
	while (f->cols.form[++i] != NULL)
	{
		write(f->out_fd, f->cols.form[i], strlen(f->cols.form[i]));
		write(f->out_fd, "\n", 1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_formatter	*f;

	if (argc < 5 || argc > 7)
		return (usage(argv[0]));
	f = init_formatter(&argv[1]);
	if (f == NULL)
		return (1);
	if (retrive_data(f) || format_data(f) || save_data(f))
		return (1);
	free_formatter(f);
	return (0);
}
