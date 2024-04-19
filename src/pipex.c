/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/04/19 21:41:59 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void
	forking(
		int input,
		int output)
{
	dup2(input, STDIN_FILENO);
	close(input);
	dup2(output, STDOUT_FILENO);
	close(output);
	
}

int
	main(
		int argc,
		char **argv,
		char **envp)
{
	int	i;
	int	infile;
	int	outfile;
	int	fds[2];
	int	pid;

	if (argc < 5)
		return (EXIT_FAILURE);
	if (pipe(fds) == -1)
		return (EXIT_FAILURE);
	infile = open(argv[argc - 1], O_RDONLY);
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
	pid = fork();
	if (pid == 0)
		forking(infile, fds[1]);
	else
		forking(fds[0], outfile);
	return (0);
}
