#include "column_formatter.h"

int	alloc_form(t_formatter *f)
{
	size_t	i;
	size_t	size;

	i = 0;
	while (f->cols.cols[i] != NULL)
		++i;
	size = 1;
	size += (f->height + 1) * (i / (f->height * f->max));
	//printf("%ld %ld ", i, i / (f->height * f->max));
	i %= (f->height * f->max);
	if (i > (size_t)f->height)
		size += f->height;
	else
		size += i;
	//printf("%ld %ld\n", size, i);
	f->cols.form = malloc(sizeof(char *) * size);
	if (f->cols.form == NULL)
		return (raise_error_i("malloc error", f));
	return (0);
}

int	save_column(t_formatter *f, int i)
{
	size_t	index;
	size_t	old_len;
	size_t	col_len;
	size_t	offset;

	index = i % f->height + f->cols.curr * (f->height + 1);
	old_len = strlen(f->cols.form[index]);
	col_len = strlen(f->cols.cols[i + f->cols.curr * (f->max * f->height)]) + 1;
	offset = old_len + f->dist;
	f->cols.form[index] = realloc_str(f->cols.form[index], offset + col_len);
	if (f->cols.form[index] == NULL)
		return (raise_error_i("malloc error", f));
	memset(&f->cols.form[index][old_len], (int) ' ', f->dist);
	strncpy(&f->cols.form[index][offset], f->cols.cols[i + f->cols.curr * (f->max * f->height)], col_len);
	return (0);
}

int	save_columns(t_formatter *f)
{
	int	i;

	f->cols.curr = 0;
	if (alloc_form(f))
		return (1);
	i = -1;
	while (f->cols.cols[++i + f->cols.curr * (f->max * f->height)] != NULL)
	{
		//printf("%d\n", i + f->cols.curr * (f->max * f->height));
		if (i < f->height)
		{
			int j = i % f->height + f->cols.curr * (f->height + 1); // fix
			f->cols.form[j] = strdup(f->cols.cols[i + f->cols.curr * (f->max * f->height)]);
			if (f->cols.form[j] == NULL)
				return (raise_error_i("malloc error", f));
			continue ;
		}
		if (save_column(f, i))
			return (1);
		if (((i + 1) / f->height) >= f->max)
		{
			i = -1;
			f->cols.form[++(f->cols.curr) * (f->height + 1) - 1] = strdup(PAGE_SEPARATOR);
		}
	}
	f->cols.form[(f->cols.curr + 1) * (f->height + 1) - 1] = NULL;
	return (0);
}
