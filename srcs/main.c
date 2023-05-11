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

char	*format_spaces(char *s, int spaces, int many, size_t line_len, size_t len)
{
	char	*n;
	int		count;
	size_t	i;
	int		space_count;

	i = -1;
	n = malloc(sizeof(char) * (line_len + 1));
	if (n == NULL)
		return (NULL);
	n[line_len] = '\0';
	bzero(n, line_len);	//removeme
	count = 0;
	printf("len %d %d %ld\n", spaces, many, len);
	while (s[++i] != '\0' && (i < len))
	{
		printf("%ld %d %d |%s|\n", i, count, many, n);
		if (s[i] != ' ')
			n[i + count] = s[i];
		else
		{
			//if (many > 0)
			//	--many;
			if (many == 0)
				spaces -= 1;
			--many;
			space_count = spaces + 2;
			printf("%d %d\n", space_count, (int)(i + count));
			while (--space_count >= 0)
				n[i + count++] = ' ';
			--count;
			printf("%d %d\n", space_count, (int)(i + count));
		}
	}
	printf("%ld %d %d |%s|\n", i, count, many, n);
	printf("\n\n|%s| %ld\n", n, strlen(n));
	return (n);
}

int	format_data(t_formatter *f)
{
	char	*space;
	size_t	curr;
	size_t	offset;
	size_t	len;
	int		i;
	int		curr_col;
	int		spaces;
	int		many;

	i = -1;
	curr_col = 0;
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
		while (curr < len)
		{
			f->cols.cols = realloc_matr(f->cols.cols, curr_col + 2);
			if (f->cols.cols == NULL)
				return (raise_error_i("malloc error", f));
			f->cols.cols[curr_col + 1] = NULL;
			while (f->cols.rows[i][curr] == ' ')
				++curr;
			printf("curr |%ld|%ld|%d|\n", curr, len ,f->width);
			if ((curr + f->width) >= len)
			{
				printf("curr |%ld|%ld|%d|\n", curr, len ,f->width);
				f->cols.cols[curr_col++] = strdup(&f->cols.rows[i][curr]);
				break ;
			}
			printf("str |%s|\n", &f->cols.rows[i][curr]);
			space = rstrnchr(&f->cols.rows[i][curr], ' ', f->width + 1);
			printf("space |%s|\n", space);
			if (space == NULL)
			{
				f->cols.cols[curr_col++] = strndup(&f->cols.rows[i][curr], f->width);
				break ;
			}
			offset = (size_t)(space - &f->cols.rows[i][curr]);
			printf("space |%ld|\n", offset);
			spaces = (f->width - offset) / count_spaces_to_add(&f->cols.rows[i][curr], offset);
			many = (f->width - offset) % count_spaces_to_add(&f->cols.rows[i][curr], offset);

			printf("spaces |%d|%ld|%d|\n", spaces, (f->width - offset), count_spaces_to_add(&f->cols.rows[i][curr], offset));

			f->cols.cols[curr_col] = format_spaces(&f->cols.rows[i][curr], spaces, many, f->width, offset);
			if (f->cols.cols[curr_col++] == NULL)
				return (raise_error_i("malloc error", f));
			curr += offset;
			printf("\n\n|%s|\n\n", f->cols.cols[curr_col-1]);
		}
	}
	return (0);
}

int	save_data(t_formatter *f)
{
	unsigned int	i;

	i = -1;
	while (f->cols.cols[++i] != NULL)
	{
		write(f->out_fd, f->cols.cols[i], strlen(f->cols.cols[i]));
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
