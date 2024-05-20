/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/20 22:35:22 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// sets previous child's pipe as input, makes a new pipe and sets it as output
//	then returns new pipe's read end to parent for next child
static int
	fork_them_kids(
		int input_fd,
		char *command,
		char **envp)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (dup2(input_fd, STDIN_FILENO) == -1)
		error_exit(0, command);
	if (close(input_fd) == -1)
		error_exit(0, command);
	if (pipe(pipe_fds) == -1)
		error_exit(0, command);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		error_exit(0, command);
	if (close(pipe_fds[1]) == -1)
		error_exit(0, command);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fds[0]);
		execute(command, envp);
	}
	return (pipe_fds[0]);
}

// output to specific fd instead a new pipe
static pid_t
	favourite_child(
		int input_fd,
		int	output_fd,
		char *command,
		char **envp)
{
	pid_t	pid;

	if (dup2(input_fd, STDIN_FILENO) == -1)
		error_exit(0, command);
	if (close(input_fd) == -1)
		error_exit(0, command);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		error_exit(0, command);
	if (close(output_fd) == -1)
		error_exit(0, command);;
	pid = fork();
	if (pid == 0)
		execute(command, envp);
	return (pid);
}

static void
	zombie_prevention_protocol(
		int pid,
		int i)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		while (i-- > 2)
			if (wait(NULL) == -1)
				error_exit(0, NULL);
		exit(WEXITSTATUS(status));
	}
	exit(errno);
}

int
	main(
		int argc,
		char **argv,
		char **envp)
{
	pid_t	pid;
	int		file_fd;
	int		input_fd;
	int		i;

	if (argc < 5)
		error_exit(EINVAL, NULL);
	file_fd = open_infile(argv[1]);
	input_fd = fork_them_kids(file_fd, argv[2], envp);
	i = 2;
	while (i++ < argc - 3)
	{
		input_fd = fork_them_kids(input_fd, argv[i], envp);
	}
	file_fd = open_outfile(argv[argc - 1]);
	pid = favourite_child(input_fd, file_fd, argv[argc - 2], envp);
	zombie_prevention_protocol(pid, i);
}
