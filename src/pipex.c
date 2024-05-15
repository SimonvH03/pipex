/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/15 18:32:48 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// checks argc, opens infile, creates pipe[0], inits outile_fd
static void
	init(
		int *inout_fds,
		int *pipe_fds,
		int argc,
		char **argv)
{
	if (argc < 5)
		error_exit(ERR_ARGS);
	if (pipe(pipe_fds) == -1)
		error_exit(ERR_PIPE);
	inout_fds[0] = open(argv[1], O_RDONLY);
	if (inout_fds[0] == -1)
		error_exit(ERR_OPEN);
	inout_fds[1] = -1;
}

static void
	open_outfile(
		int *inout_fds,
		char *outfile)
{
	inout_fds[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (inout_fds[1] == -1)
		error_exit(ERR_OPEN);
}

// closes unused fds, then sets output and input to STD_FILENO
static void
	kids_handle_fds(
		int *input,
		int *output)
{
	ft_close(&output[0]);
	ft_close(&input[1]);
	dup2(output[1], STDOUT_FILENO);
	ft_close(&output[1]);
	dup2(input[0], STDIN_FILENO);
	ft_close(&input[0]);
}

pid_t
	fork_them_kids(
		int *input_fds,
		int *output_fds,
		char *command,
		char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		kids_handle_fds(input_fds, output_fds);
		execute(command, envp);
		error_exit(ERR_EXIT);
	}
	return (pid);
}

int
	main(
		int argc,
		char **argv,
		char **envp)
{
	pid_t	pid;
	int		inout_fds[2];
	int		pipe_fds[2][2];
	bool	curr;
	int		status;
	int		i;

	curr = 0;
	init(inout_fds, pipe_fds[curr], argc, argv);
	i = 2;
	pid = fork_them_kids(inout_fds, pipe_fds[curr], argv[i], envp);
	ft_printf("%s\t: %d\n", argv[i], pid);
	ft_close(&inout_fds[0]);
	while (i++ < argc - 3)
	{
		pipe(pipe_fds[!curr]);
		pid = fork_them_kids(pipe_fds[curr], pipe_fds[!curr], argv[i], envp);
		ft_printf("%s\t: %d\n", argv[i], pid);
		ft_close(&pipe_fds[curr][0]); // Close unused read for parent
		ft_close(&pipe_fds[curr][1]); // Close input write end for kid
		curr = !curr;
	}
	open_outfile(inout_fds, argv[argc - 1]);
	pid = fork_them_kids(pipe_fds[curr], inout_fds, argv[argc - 2], envp);
	ft_printf("%s\t: %d\n", argv[argc - 2], pid);
	ft_close(&pipe_fds[curr][0]);
	ft_close(&pipe_fds[curr][1]);
	ft_close(&inout_fds[1]);
	waitpid(pid, &status, 0);
	while (i-- >= 2)
		ft_printf("closed: %d\n", wait(NULL));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
