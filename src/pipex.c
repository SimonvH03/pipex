/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/01 00:04:31 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void
	init(
		int	*file_fds,
		int	*pipe_fds,
		int argc,
		char **argv)
{
	if (argc < 5)
		error_exit(-1, ERR_ARGS);
	if (pipe(pipe_fds) == -1)
		error_exit(-1, ERR_PIPE);
	file_fds[0] = open(argv[1], O_RDONLY);
	if (file_fds[0] == -1)
		error_exit(-1, ERR_OPEN);
	file_fds[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fds[1] == -1)
		error_exit(-1, ERR_OPEN);
}

void
	set_input_output(
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
	pid_t	pid;
	int		file_fds[2];
	int		pipe_fds[2];

	init(file_fds, pipe_fds, argc, argv);
	pid = fork();
	if (pid == 0)
	{
		set_input_output(file_fds[0], pipe_fds[1]);
		execute(pid, argv[2], envp);
	}
	else
	{
		close(pipe_fds[1]);
		set_input_output(pipe_fds[0], file_fds[1]);
		execute(pid, argv[3], envp);
	}
	error_exit(pid, ERR_EXIT);
}
