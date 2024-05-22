/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/22 23:26:32 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int
	fork_up_the_first_one(
		char *infile,
		char *command,
		char **envp)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		error_exit(0, command);
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
static int
	fork_them_kids(
		int input_fd,
		char *command,
		char **envp)
{
	pid_t	pid;
	int		pipe_fds[2];

	set_input(input_fd);
	if (pipe(pipe_fds) == -1)
		error_exit(0, command);
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
static pid_t
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

static int
	zombie_prevention_protocol(
		int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		error_exit(0, NULL);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	return (errno);
}

int
	main(
		int argc,
		char **argv,
		char **envp)
{
	pid_t	pid;
	int		input_fd;
	int		i;

	if (argc < 5)
		error_exit(EINVAL, NULL);
	input_fd = fork_up_the_first_one(argv[1], argv[2], envp);
	i = 2;
	while (i++ < argc - 3)
	{
		input_fd = fork_them_kids(input_fd, argv[i], envp);
	}
	pid = favourite_child(input_fd, argv[argc - 1], argv[argc - 2], envp);
	return (zombie_prevention_protocol(pid));
}
