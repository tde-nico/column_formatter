#include "column_formatter.h"

int	count_spaces(char *s, size_t len)
{
	int		count;
	size_t	i;

	count = 0;
	i = -1;
	while (s[++i] != '\0' && i < len)
	{
		if (s[i] == ' ')
			++count;
	}
	return (count);
}

char	*format_spaces(char *s, int spaces, int many, size_t lens[2])
{
	char	*n;
	int		counts[2];
	size_t	i;

	i = -1;
	n = malloc(sizeof(char) * (lens[0] + 1));
	if (n == NULL)
		return (NULL);
	bzero(n, lens[0] + 1);
	counts[0] = 0;
	while (s[++i] != '\0' && (i < lens[1]))
	{
		if (s[i] != ' ')
			n[i + counts[0]] = s[i];
		else
		{
			if (many-- == 0)
				spaces -= 1;
			counts[1] = spaces + 2;
			while (--counts[1] >= 0)
				n[i + counts[0]++] = ' ';
			--counts[0];
		}
	}
	return (n);
}

int	format_line(t_formatter *f, char *space, int i, int width)
{
	size_t	offset;
	int		count_space;
	size_t	lens[2];

	offset = (size_t)(space - &f->cols.rows[i][f->curr_char]);
	count_space = count_spaces(&f->cols.rows[i][f->curr_char], offset);
	if (width != f->width)
		width -= (utf8_offset(&f->cols.rows[i][f->curr_char], width)
				- utf8_offset(&f->cols.rows[i][f->curr_char], offset));
	lens[0] = width;
	lens[1] = offset;
	if (!count_space)
		count_space = width - offset;
	f->cols.cols[f->cols.curr] = format_spaces(
			&f->cols.rows[i][f->curr_char],
			(width - offset) / count_space,
			(width - offset) % count_space,
			lens);
	if (f->cols.cols[(f->cols.curr)++] == NULL)
		return (raise_error_i("malloc error", f));
	f->curr_char += offset;
	return (0);
}

int	format_lines(t_formatter *f, int i, int width)
{
	char	*space;

	space = rstrnchr(&f->cols.rows[i][f->curr_char], ' ', width + 1);
	if (space == NULL)
	{
		f->cols.cols[(f->cols.curr)++] = strndup(
				&f->cols.rows[i][f->curr_char], width);
		f->curr_char += width;
		return (0);
	}
	while (space > &f->cols.rows[i][f->curr_char] && space[-1] == ' ')
		--space;
	if (format_line(f, space, i, width))
		return (1);
	if (count_spaces(f->cols.cols[f->cols.curr - 1],
			strlen(f->cols.cols[f->cols.curr - 1])) == 0)
		memset(&f->cols.cols[f->cols.curr - 1][
			strlen(f->cols.cols[f->cols.curr - 1])], ' ',
			width - strlen(f->cols.cols[f->cols.curr - 1]));
	return (0);
}

int	format_column(t_formatter *f, size_t len, int i)
{
	int	width;

	while (f->curr_char < len)
	{
		f->cols.cols = realloc_matr(f->cols.cols, f->cols.curr + 2);
		if (f->cols.cols == NULL)
			return (raise_error_i("malloc error", f));
		f->cols.cols[f->cols.curr + 1] = NULL;
		while (f->cols.rows[i][f->curr_char] == ' ')
			(f->curr_char)++;
		width = f->width + utf8_offset(
				&f->cols.rows[i][f->curr_char], f->width);
		if (width < f->width)
			return (raise_error_i("not UFT-8 text", f));
		if ((f->curr_char + width) >= len)
		{
			f->cols.cols[(f->cols.curr)++] = strdup(
					&f->cols.rows[i][f->curr_char]);
			break ;
		}
		if (format_lines(f, i, width))
			return (1);
	}
	return (0);
}
