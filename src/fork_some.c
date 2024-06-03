/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_some.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:28:50 by simon             #+#    #+#             */
/*   Updated: 2024/06/03 21:05:50 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// so when a man and a woman love each other very much...
int
	fork_up_the_first_one(
		char *infile,
		char *command,
		char **envp)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		error_exit(errno, command);
	set_output(pipe_fds[1]);
	pid = fork();
	if (pid == 0)
	{
		set_input(open_infile(infile));
		close(pipe_fds[0]);
		execute(command, envp);
	}
	return (pipe_fds[0]);
}

// sets previous child's pipe as input, makes a new pipe and sets it as output
//	then returns new pipe's read end to parent for next child
int
	fork_them_kids(
		int input_fd,
		char *command,
		char **envp)
{
	pid_t	pid;
	int		pipe_fds[2];

	set_input(input_fd);
	if (pipe(pipe_fds) == -1)
		error_exit(errno, command);
	set_output(pipe_fds[1]);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fds[0]);
		execute(command, envp);
	}
	return (pipe_fds[0]);
}

// output to specific fd instead a new pipe
pid_t
	favourite_child(
		int input_fd,
		char *outfile,
		char *command,
		char **envp)
{
	pid_t	pid;

	set_input(input_fd);
	pid = fork();
	if (pid == 0)
	{
		set_output(open_outfile(outfile));
		execute(command, envp);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (pid);
}
