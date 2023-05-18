#include "column_formatter.h"

/**
 * @brief a custom wrap for atoi for more secure conversion
 * @param value the string to be converted into a number
 * @return -1 if not a valid number, otherwise the number as int
 * 
 * a custom wrap for atoi that checks if the string exists, is not empty and
 * in only digit based and then it calls atoi on te string
*/
size_t	xatoi(char *value)
{
	size_t	i;

	if (value == NULL || value[0] == '\0')
		return (0);
	i = 0;
	while (value[i] != '\0')
	{
		if (!isdigit(value[i++]))
			return (0);
	}
	return ((size_t)atoi(value));
}

/**
 * @brief inits the formatter struct and parses the columns datas
 * @param f the formatter struct
 * @param args the arguments (argv) containing the column-infos
 * @return 0 by default, 1 if error
 * 
 * for every one of the four numeric parameters checks if they are valid
 * if not it raise an error, and then it set some defaults values on the
 * other struct field for the columns formatting
*/
int	init_columns(t_formatter *f, char **args)
{
	f->max = xatoi(args[0]);
	if (f->max < 1)
		return (raise_error_i("invalid columns_per_page", f));
	f->height = xatoi(args[1]);
	if (f->height < 1)
		return (raise_error_i("invalid columns_height", f));
	f->width = xatoi(args[2]);
	if (f->width < 1)
		return (raise_error_i("invalid columns_width", f));
	f->dist = xatoi(args[3]);
	if (f->dist < 1)
		return (raise_error_i("invalid columns_distance", f));
	f->cols.form = NULL;
	f->cols.cols = NULL;
	f->cols.rows = NULL;
	f->cols.curr = 0;
	return (0);
}

/**
 * @brief init the files for input and output
 * @param f the formatter struct
 * @param in_fname the input file name (if empty -> stdin)
 * @param out_fname the output file name (if empty -> stdout)
 * @return 0 by default, 1 if error
 * 
 * it checks if the file_name of the input file in not null or empty, then if
 * the file exists, does the same operations on the output file, by default
 * if none is specified, standard input (0) and standard output (1) are used
*/
int	init_files(t_formatter *f, char *in_fname, char *out_fname)
{
	f->in_fd = STDIN_FILENO;
	f->out_fd = STDOUT_FILENO;
	if (in_fname == NULL || in_fname[0] == '\0')
		return (0);
	f->in_fd = open(in_fname, O_RDONLY);
	if (f->in_fd < 0)
		return (raise_error_i("invalid input file", f));
	if (out_fname != NULL && out_fname[0] != '\0')
		f->out_fd = open(out_fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (f->out_fd < 0)
		return (raise_error_i("error while opening output file", f));
	return (0);
}

/**
 * @brief initialize all the components of the main struct
 * @param args the arguments of the program
 * @return the formatter struct (main struct)
 * 
 * the formatter struct is allocated and the standard files as set then it
 * calls the "init_columns" and "init_files" functions to initialize the
 * columns data and the file descriptors
*/
t_formatter	*init_formatter(char **args)
{
	t_formatter	*f;

	f = (t_formatter *)malloc(sizeof(t_formatter) * 1);
	if (f == NULL)
		return (raise_error_p("malloc error", NULL));
	if (init_columns(f, args))
		return (NULL);
	if (init_files(f, args[4], args[5]))
		return (NULL);
	return (f);
}
