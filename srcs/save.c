#include "column_formatter.h"

int	save_column(t_formatter *f, int i)
{
	size_t	index;
	size_t	old_len;
	size_t	col_len;
	size_t	offset;

	index = i % f->height;
	old_len = strlen(f->cols.form[index]);
	col_len = strlen(f->cols.cols[i]) + 1;
	offset = old_len + f->dist;
	f->cols.form[index] = realloc_str(f->cols.form[index], offset + col_len);
	if (f->cols.form[index] == NULL)
		return (raise_error_i("malloc error", f));
	memset(&f->cols.form[index][old_len], (int) ' ', f->dist);
	strncpy(&f->cols.form[index][offset], f->cols.cols[i], col_len);
	return (0);
}

int	save_columns(t_formatter *f)
{
	int		i;

	f->cols.form = malloc(sizeof(char *) * (f->height + 1));
	if (f->cols.form == NULL)
		return (raise_error_i("malloc error", f));
	i = -1;
	while (f->cols.cols[++i] != NULL)
	{
		if (i < f->height)
		{
			f->cols.form[i % f->height] = strdup(f->cols.cols[i]);
			if (f->cols.form[i % f->height] == NULL)
				return (raise_error_i("malloc error", f));
			continue ;
		}
		if (save_column(f, i))
			return (1);
	}
	return (0);
}
