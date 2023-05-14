#include "column_formatter.h"

/**
 * @brief formats a string by padding every word with the right amount of spaces
 * @param s the string to format
 * @param spaces the amount of spaces to add per word
 * @param many the amount of extra spaces to add per word
 * @param lens two len: the first is the length of the resulting string,
 * the second is the length of the initial string
 * @return the new formatted string, if an error occours: NULL
 * 
 * it creates a new string as the original line but the spaces are
 * redistributed or added to create padding for the allignement
*/
char	*format_spaces(char *s, size_t spaces, size_t many, size_t lens[2])
{
	char	*n;
	int		i;
	int		counts[2];

	i = -1;
	n = malloc(sizeof(char) * (lens[0] + 1));
	if (n == NULL)
		return (NULL);
	bzero(n, lens[0] + 1);
	counts[0] = 0;
	while (s[++i] != '\0' && (i < (int)lens[1]))
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

/**
 * @brief formats a line by evaluating and adding the needed spaces
 * @param f the formatter struct
 * @param space a pointer at the end of the current line to format
 * @param i the current row that is been analyzed
 * @param width the width of the current line in characters (UTF-8)
 * @return 0 by default, 1 if error
 * 
 * after counting the number of spaces in the current string and evaluating the
 * offset for utf-8 characters, it format the tring with the "format_spaces"
 * function
*/
int	format_line(t_formatter *f, char *space, size_t i, size_t width)
{
	size_t	offset;
	size_t	count_space;
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

/**
 * @brief formats a set of lines by parsing an input row
 * @param f the formatter struct
 * @param i the current row that is been analyzed
 * @param width the width of the current line in characters (UTF-8)
 * @return 0 by default, 1 if error
 * 
 * initialy the function finds the last possible word, if one big word it
 * will be splitted, then a line is formatted and if it was a one word only
 * the line is filled to width with spaces
*/
int	format_lines(t_formatter *f, size_t i, size_t width)
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
	if (format_line(f, space, i, width))
		return (1);
	if (count_spaces(f->cols.cols[f->cols.curr - 1],
			strlen(f->cols.cols[f->cols.curr - 1])) == 0)
	{
		memset(&f->cols.cols[f->cols.curr - 1][
			strlen(f->cols.cols[f->cols.curr - 1])], ' ',
			width - strlen(f->cols.cols[f->cols.curr - 1]));
	}
	return (0);
}

/**
 * @brief formats the last piece of the current row
 * @param f the formatter struct
 * @param width the width of the current line in characters (UTF-8)
 * @param i the current row that is been analyzed
 * @return 0 by default, 1 if error
 * 
 * the last line has no need to be formatted, so it will be copied and filled
 * with spaces to width
*/
int	format_last_line(t_formatter *f, size_t i, size_t width)
{
	size_t	len;

	len = strlen(&f->cols.rows[i][f->curr_char]);
	f->cols.cols[f->cols.curr] = malloc(sizeof(char) * (width + 1));
	if (f->cols.cols[f->cols.curr] == NULL)
		return (raise_error_i("malloc error", f));
	strncpy(f->cols.cols[f->cols.curr], &f->cols.rows[i][f->curr_char], width);
	memset(&f->cols.cols[f->cols.curr][len - 1], (int) ' ', width - len + 1);
	f->cols.cols[(f->cols.curr)++][width] = '\0';
	return (0);
}

/**
 * @brief formats a paragraph by parsing a row into lines
 * @param f the formatter struct
 * @param len the length of the current row
 * @param i the current row that is been analyzed
 * @return 0 by default, 1 if error
 * 
 * after expanding the format matrix, it evaluates the width of the current
 * line for the final columns
*/
int	format_column(t_formatter *f, size_t len, size_t i)
{
	size_t	width;

	while (f->curr_char < len)
	{
		f->cols.cols = realloc_matr(f->cols.cols, f->cols.curr + 2);
		if (f->cols.cols == NULL)
			return (raise_error_i("malloc error", f));
		while (f->cols.rows[i][f->curr_char] == ' ')
			(f->curr_char)++;
		width = f->width + utf8_offset(
				&f->cols.rows[i][f->curr_char], f->width);
		if (width < f->width)
			return (raise_error_i("not UFT-8 text", f));
		if ((f->curr_char + width) >= len)
		{
			if (format_last_line(f, i, width))
				return (1);
			break ;
		}
		if (format_lines(f, i, width))
			return (1);
	}
	return (0);
}
