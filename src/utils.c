/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:30:02 by simon             #+#    #+#             */
/*   Updated: 2024/05/20 22:05:16 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void
	error_exit(
		int i,
		char *param)
{
	const char *nill = "\0";

	if (i > 0)
		errno = i;
	if (param == NULL)
		param = (char *)nill;
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("pipex: %s: %s\n", strerror(errno), param);
	exit(errno);
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
