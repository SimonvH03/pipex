/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/15 19:49:57 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void
	open_outfile(
		int *inout_fds,
		char *outfile)
{
	inout_fds[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (inout_fds[1] == -1)
		error_exit(ERR_OPEN);
}

static void
	open_infile(
		int *inout_fds,
		char *infile)
{
	inout_fds[0] = open(infile, O_RDONLY);
	if (inout_fds[0] == -1)
		error_exit(ERR_OPEN);
}

pid_t
	fork_them_kids(
		char *command,
		char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execute(command, envp);
		error_exit(ERR_EXIT);
	}
	return (pid);
}

static void
	set_fds(
		int *input,
		int *output)
{
	dup2(input[0], STDIN_FILENO);
	ft_close(&input[0]);
	dup2(output[1], STDOUT_FILENO);
	ft_close(&output[1]);
}

int
	main(
		int argc,
		char **argv,
		char **envp)
{
	pid_t	pid;
	int		inout_fds[2];
	int		pipe_fds[2];
	int		status;
	int		i;

	if (argc < 5)
		error_exit(ERR_ARGS);
	if (pipe(pipe_fds) == -1)
		error_exit(ERR_PIPE);
	open_infile(inout_fds, argv[1]);

	i = 2;
	set_fds(inout_fds, pipe_fds);
	pid = fork();
	if (pid == 0)
	{
		ft_close(&pipe_fds[0]);
		execute(argv[i], envp);
	}

	ft_close(&inout_fds[0]);

	while (i++ < argc - 3)
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		ft_close(&pipe_fds[0]);

		pipe(pipe_fds);

		dup2(pipe_fds[1], STDOUT_FILENO);
		ft_close(&pipe_fds[1]);

		pid = fork();
		if (pid == 0)
		{
			ft_close(&pipe_fds[0]);
			execute(argv[i], envp);
		}
	}

	open_outfile(inout_fds, argv[argc - 1]);

	set_fds(pipe_fds, inout_fds);
	pid = fork();
	if (pid == 0)
	{
		ft_close(&inout_fds[0]);
		execute(argv[i], envp);
	}

	ft_close(&inout_fds[1]);

	waitpid(pid, &status, 0);
	while (i-- >= 2)
		wait(NULL);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
