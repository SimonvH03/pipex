/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:30:02 by simon             #+#    #+#             */
/*   Updated: 2024/05/22 23:33:45 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void
	error_exit(
		int i,
		char *param)
{
	const char	*nill = "\0";

	if (i > 0)
		errno = i;
	if (param == NULL)
		param = (char *)nill;
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("pipex: %s: %s\n", strerror(errno), param);
	exit(errno);
}

void
	set_input(
		int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		error_exit(0, NULL);
	if (close(input_fd) == -1)
		error_exit(0, NULL);
}

void
	set_output(
		int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		error_exit(0, NULL);
	if (close(output_fd) == -1)
		error_exit(0, NULL);
}

int
	open_infile(
		char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		error_exit(0, infile);
	return (fd);
}

int
	open_outfile(
		char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		error_exit(0, outfile);
	return (fd);
}
