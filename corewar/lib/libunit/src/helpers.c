#include <stdio.h>
#include <unistd.h>
#include "libft.h"

static int g_pipe[2];
static int g_backup;

/*
** start_fd_capture - Start a capture of a file descriptor
** @fd: File descriptor to capture from
**
** start_fd_capture will capture data written to @fd.
** stop_fd_capture should be called afterwards to retrieve the output.
**
** /!\ These functions don't yet support multiple captures in parallel!
** /!\ These functions rely on a unix pipe, and write() may block if the pipe
** limit is reached (65536 on Linux).
**
** Return: On success 0. On error -1, and errno shall be set to indicate the
** error.
*/

int start_fd_capture(int fd)
{
	if (pipe(g_pipe) == -1)
		return (-1);
	if ((g_backup = dup(fd)) == -1)
		return (-1);
	if (dup2(g_pipe[1], fd) == -1)
		return (-1);
	return (0);
}

/*
** stop_fd_capture - Stop a capture of a file descriptor
** @fd: File descriptor to stop capture from
** @output: Pointer to which the capture will be writen to
**
** stop_fd_capture() will set @output to the content that was output to @fd
** since start_fd_capture() was called.
**
** We really shouldn't flush the FILE streams for the caller, but we still do it
** as a convenience.
**
** Return: The number of bytes written to @output on success. On error -1.
*/

int stop_fd_capture(int fd, char **output)
{
	int ret;

	// We can't flush the specific FILE streams that would wrap @fd, so instead
	// we flush all streams.
	if (fflush(NULL) != 0)
		return (-1);
	if (close(g_pipe[1]) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	if ((ret = ft_read_all(g_pipe[0], output)) == -1)
		return (-1);
	if (close(g_pipe[0]) == -1)
		return (-1);
	if (dup2(g_backup, fd) == -1)
		return (-1);
	if (close(g_backup) == -1)
		return (-1);
	return (ret);
}
