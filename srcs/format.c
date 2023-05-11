#include "column_formatter.h"

int	count_spaces_to_add(char *s, size_t len)
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

int	format_line(t_formatter *f, size_t *curr, char *space, int i)
{
	size_t	offset;
	int		count_spaces;
	int		spaces;
	int		many;
	size_t	lens[2];

	if (space == NULL)
	{
		f->cols.cols[(f->cols.curr)++] = strndup(
				&f->cols.rows[i][*curr], f->width);
		return (0);
	}
	offset = (size_t)(space - &f->cols.rows[i][*curr]);
	count_spaces = count_spaces_to_add(&f->cols.rows[i][*curr], offset);
	spaces = (f->width - offset) / count_spaces;
	many = (f->width - offset) % count_spaces;
	lens[0] = f->width;
	lens[1] = offset;
	f->cols.cols[f->cols.curr] = format_spaces(
			&f->cols.rows[i][*curr], spaces, many, lens);
	if (f->cols.cols[(f->cols.curr)++] == NULL)
		return (raise_error_i("malloc error", f));
	*curr += offset;
	return (0);
}

int	format_lines(t_formatter *f, size_t *curr, size_t len, int i)
{
	char	*space;

	while (*curr < len)
	{
		f->cols.cols = realloc_matr(f->cols.cols, f->cols.curr + 2);
		if (f->cols.cols == NULL)
			return (raise_error_i("malloc error", f));
		f->cols.cols[f->cols.curr + 1] = NULL;
		while (f->cols.rows[i][*curr] == ' ')
			(*curr)++;
		if ((*curr + f->width) >= len)
		{
			f->cols.cols[(f->cols.curr)++] = strdup(&f->cols.rows[i][*curr]);
			break ;
		}
		space = rstrnchr(&f->cols.rows[i][*curr], ' ', f->width + 1);
		if (format_line(f, curr, space, i))
			return (1);
	}
	return (0);
}

int	format_data(t_formatter *f)
{
	size_t	curr;
	size_t	len;
	int		i;

	i = -1;
	f->cols.cols = malloc(sizeof(char *) * 2);
	if (f->cols.cols == NULL)
		return (raise_error_i("malloc error", f));
	f->cols.cols[1] = NULL;
	while (f->cols.rows[++i] != NULL)
	{
		if (f->cols.rows[i][0] == '\n')
			continue ;
		curr = 0;
		len = strlen(f->cols.rows[i]);
		if (format_lines(f, &curr, len, i))
			return (1);
	}
	return (0);
}
