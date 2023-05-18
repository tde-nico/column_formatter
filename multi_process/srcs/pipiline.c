#include "column_formatter.h"

/**
 * @brief forks the process ad enstablishes a pipeline between processes
 * @param f the main formatter struct
 * @param fun the function that will be called in the forked prcess
 * @param in_fd the input fd that will be duplicated
 * @param fd the two pipeline's file descriptors
 * 
 * duplicates the needed file descriptors, then launches the worker and
 * finally frees all the resources
*/
void	worker(t_formatter *f, int (*fun)(t_formatter *f), int in_fd, int fd[2])
{
	if (fun != &retrive_data_wrapper)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		in_fd = STDIN_FILENO;
	}
	if (fun != &save_data_wrapper)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		in_fd = STDOUT_FILENO;
	}
	close(fd[0]);
	if (fun(f))
		exit(1);
	free_formatter(f);
	exit(0);
}

/**
 * @brief forks the process ad enstablishes a pipeline between processes
 * @param f the main formatter struct
 * @param in_fd the input fd that will be duplicated
 * @param fun the function that will be called in the forked prcess
 * @return a negative number by default (representing the output fd), if an
 * error occours: 1
 * 
 * creates a pipiline, forks the process and launches a worker on the child,
 * instead if the worker is the last one the father waits all the children
*/
int	exec(t_formatter *f, int in_fd, int (*fun)(t_formatter *f))
{
	pid_t	pid;
	int		fd[2];
	int		status;

	status = 0;
	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (raise_error_i("fork error", f));
	if (pid == 0)
		worker(f, fun, in_fd, fd);
	close(in_fd);
	close(fd[1]);
	if (fun == &save_data_wrapper)
		waitpid(-1, &status, WUNTRACED);
	if (WEXITSTATUS(status) == 1)
		return (1);
	return (-fd[0] - 1);
}

/**
 * @brief executes in pipeline the three main processes (retrive, format, save)
 * @param f the main formatter struct
 * @return 0 by default, if an error occours: 1
 * 
 * if the number of arguments is incompatible it returns error by printing
 * the usage of the program, then it initialize the formatter (main structure)
 * and after manipulating the data it frees all the allocated mamories
*/
int	pipeline(t_formatter *f)
{
	int	tmp_fd;

	tmp_fd = dup(f->in_fd);
	tmp_fd = exec(f, tmp_fd, &retrive_data_wrapper);
	if (tmp_fd > 0)
		return (1);
	tmp_fd = -tmp_fd - 1;
	tmp_fd = exec(f, tmp_fd, &format_data_wrapper);
	if (tmp_fd > 0)
		return (1);
	tmp_fd = -tmp_fd - 1;
	tmp_fd = exec(f, tmp_fd, &save_data_wrapper);
	if (tmp_fd > 0)
		return (1);
	tmp_fd = -tmp_fd - 1;
	close(tmp_fd);
	return (0);
}
