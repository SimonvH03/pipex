/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/16 21:13:28 by svan-hoo         ###   ########.fr       */
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

	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	if (pipe(pipe_fds) == -1)
		error_exit(0);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
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

	ft_printf("input: %i\noutput: %i\n", input_fd, output_fd);
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	ft_printf("input: %i\noutput: %i\n", input_fd, output_fd);
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
				error_exit(0);
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
		error_exit(EINVAL);
	file_fd = open_infile(argv[1]);
	input_fd = fork_them_kids(file_fd, argv[2], envp);
	close(file_fd);
	i = 2;
	while (i++ < argc - 3)
	{
		input_fd = fork_them_kids(input_fd, argv[i], envp);
	}
	file_fd = open_outfile(argv[argc - 1]);
	// if (input_fd == file_fd)
	// 	error_exit(5);
	pid = favourite_child(input_fd, file_fd, argv[argc - 2], envp);
	close(file_fd);
	zombie_prevention_protocol(pid, i);
}
