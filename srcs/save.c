#include "column_formatter.h"

/**
 * @brief allocates the array for the output data
 * @param f the formatter struct
 * @return 0 by default, 1 if error
 * 
 * after the evaluation of the size of the input data it finds out how many
 * pages will be stored and how long is the last page to allocate the needed
 * memory
*/
int	alloc_form(t_formatter *f)
{
	size_t	i;
	size_t	size;

	i = 0;
	while (f->cols.cols[i] != NULL)
		++i;
	size = (f->height + 1) * (i / (f->height * f->max));
	i %= (f->height * f->max);
	if (i > (size_t)f->height)
		size += f->height;
	else
		size += i;
	f->cols.form = malloc(sizeof(char *) * size);
	if (f->cols.form == NULL)
		return (raise_error_i("malloc error", f));
	return (0);
}

/**
 * @brief copies the first piece of the current output line
 * @param f the formatter struct
 * @param i the current formatted line to parse
 * @return 0 by default, 1 if error
 * 
 * it stores the duplicate of the first line on the left of the page
*/
int	save_first_line(t_formatter *f, size_t i)
{
	size_t	form_index;
	size_t	col_index;

	form_index = i % f->height + f->cols.curr * (f->height + 1);
	col_index = i + f->cols.curr * (f->max * f->height);
	f->cols.form[form_index] = strdup(f->cols.cols[col_index]);
	if (f->cols.form[form_index] == NULL)
		return (raise_error_i("malloc error", f));
	return (0);
}

/**
 * @brief stacks up the columns in the output array
 * @param f the formatter struct
 * @param i the current formatted line to parse
 * @return 0 by default, 1 if error
 * 
 * it appends a number of spaces determined by the column distance given by
 * input and then it appends the current line to the page
*/
int	save_column(t_formatter *f, int i)
{
	size_t	f_index;
	size_t	c_index;
	size_t	old_len;
	size_t	c_len;
	size_t	offset;

	f_index = i % f->height + f->cols.curr * (f->height + 1);
	c_index = i + f->cols.curr * (f->max * f->height);
	old_len = strlen(f->cols.form[f_index]);
	c_len = strlen(f->cols.cols[c_index]) + 1;
	offset = old_len + f->dist;
	f->cols.form[f_index] = realloc_str(f->cols.form[f_index], offset + c_len);
	if (f->cols.form[f_index] == NULL)
		return (raise_error_i("malloc error", f));
	memset(&f->cols.form[f_index][old_len], (int) ' ', f->dist);
	strncpy(&f->cols.form[f_index][offset], f->cols.cols[c_index], c_len);
	return (0);
}

/**
 * @brief splits in pages the formatted data and write in the output file
 * @param f the formatter struct
 * @return 0 by default, 1 if error
 * 
 * it allocate the pages for the final file, then it appends all the lines
 * from the foramtted matrix to pages by splitting by page size (to identify
 * a page there is the page separator default="\\n %%% \\n")
*/
int	save_columns(t_formatter *f)
{
	size_t	i;

	f->cols.curr = 0;
	if (alloc_form(f))
		return (1);
	i = -1;
	while (f->cols.cols[++i + f->cols.curr * (f->max * f->height)] != NULL)
	{
		if (i < (size_t)f->height)
		{
			if (save_first_line(f, i))
				return (1);
			continue ;
		}
		if (save_column(f, i))
			return (1);
		if (((i + 1) / f->height) >= (size_t)f->max)
		{
			i = -1;
			f->cols.form[++(f->cols.curr) * (f->height + 1) - 1
			] = strdup(PAGE_SEPARATOR);
		}
	}
	f->cols.form[(f->cols.curr + 1) * (f->height + 1) - 1] = NULL;
	return (0);
}
