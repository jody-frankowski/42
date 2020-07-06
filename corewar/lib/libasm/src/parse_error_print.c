/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libasm.h"
#include "libprintf.h"

/*
** We use write() because the line may contain null bytes.
*/

static void	print_source_line(int fd, t_parse_error *error)
{
	size_t	i;

	i = 0;
	while (i < error->line.len)
	{
		if (error->line.str + i == error->column)
			ft_dprintf(fd, "%s", g_parse_err_color[error->type]);
		if ((size_t)((error->line.str + i) - error->column) == error->len)
			ft_dprintf(fd, "%s", TERM_COLOR_END);
		if (error->line.str[i] == '\t')
			write(fd, "    ", 4);
		else
			write(fd, &error->line.str[i], 1);
		i++;
	}
	ft_dprintf(fd, "\n");
}

static void	print_indicator_char(int fd, char line_char, char indicator_char)
{
	if (line_char == '\t')
	{
		ft_dprintf(fd, "%c", indicator_char);
		ft_dprintf(fd, "%c", indicator_char);
		ft_dprintf(fd, "%c", indicator_char);
		ft_dprintf(fd, "%c", indicator_char);
	}
	else
		ft_dprintf(fd, "%c", indicator_char);
}

static void	print_error_indicator(int fd, t_parse_error *error)
{
	char	*column;
	size_t	i;

	column = error->line.str;
	while (column != error->column)
		print_indicator_char(fd, *column++, ' ');
	ft_dprintf(fd, "%s", g_parse_err_color[error->type]);
	if (*column == '\t')
	{
		if (error->len == 0)
			ft_dprintf(fd, "^");
		else
			ft_dprintf(fd, "^^^^");
	}
	else
		ft_dprintf(fd, "^");
	i = 1;
	while (i < error->len)
		print_indicator_char(fd, column[i++], '^');
	ft_dprintf(fd, "%s", TERM_COLOR_END);
	ft_dprintf(fd, "\n");
}

/*
** parse_error_print() - Print a t_parse_error
** @fd:       The file descriptor to print to
** @error:    The t_parse_error to print
** @filename: The filename corresponding to this error
*/

void		parse_error_print(int fd, t_parse_error *error, char *filename)
{
	size_t	col_num;

	if (error->column)
		col_num = error->column - error->line.str + 1;
	ft_dprintf(fd, "%s:", filename);
	if (error->column && error->line.str)
		ft_dprintf(fd, "%lu:%lu:", error->line_num, col_num);
	ft_dprintf(fd, " %s%s:\e[0m %s\n",
					g_parse_err_color[error->type],
					g_parse_err_type[error->type],
					g_parse_err_msg[error->msg]);
	if (error->column)
	{
		print_source_line(fd, error);
		print_error_indicator(fd, error);
	}
}

/*
** parse_error_print() - Print an array of t_parse_error
** @fd:       The file descriptor to print to
** @errors:   The array of t_parse_error to print
** @filename: The filename corresponding to this error
*/

void		parse_errors_print(int fd, t_array *errors, char *filename)
{
	size_t			i;
	t_parse_error	*error;

	i = 0;
	while (i < errors->len)
	{
		error = ft_array_get(errors, i);
		parse_error_print(fd, error, filename);
		i++;
	}
}
