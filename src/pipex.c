/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/01 21:37:11 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// checks argc, opens infile, creates pipe[0], inits outile_fd
// static void
// 	init(
// 		int	*file_fds,
// 		int	*pipe_fds,
// 		int argc,
// 		char **argv)
// {
// 	if (argc < 5)
// 		error_exit(ERR_ARGS);
// 	if (pipe(pipe_fds) == -1)
// 		error_exit(ERR_PIPE);
// 	file_fds[0] = open(argv[1], O_RDONLY);
// 	if (file_fds[0] == -1)
// 		error_exit(ERR_OPEN);
// 	file_fds[1] = -1;
// }

static void
	open_outfile(
		int	*file_fds,
		char *outfile)
{
	file_fds[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fds[1] == -1)
		error_exit(ERR_OPEN);
}

// closes unused fds, then sets output and input to STD_FILENO
static void
	handle_fds(
		int *input,
		int *output)
{
	if (output[0] != -1)
		ft_close(&output[0]);
	if (input[1] != -1)
		ft_close(&input[1]);
	dup2(output[1], STDOUT_FILENO);
	ft_close(&output[1]);
	dup2(input[0], STDIN_FILENO);
	ft_close(&input[0]);
}

pid_t
	fork_them_kids(
		int	*input_fds,
		int	*output_fds,
		char *command,
		char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		handle_fds(input_fds, output_fds);
		execute(command, envp);
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
	int		file_fds[2];
	int		pipe_fds[2][2];
	bool	curr;
	int		status;
	int		i;

	curr = 0;
	// init(file_fds, pipe_fds[curr], argc, argv);
	if (argc < 5)
		error_exit(ERR_ARGS);
	if (pipe(pipe_fds[curr]) == -1)
		error_exit(ERR_PIPE);
	file_fds[0] = open(argv[1], O_RDONLY);
	if (file_fds[0] == -1)
		error_exit(ERR_OPEN);
	file_fds[1] = -1;
	pid = fork_them_kids(file_fds, pipe_fds[curr], argv[2], envp);
	ft_close(&file_fds[0]);
	i = 2;
	while (i < argc - 3)
	{
		curr = !curr;
		pipe(pipe_fds[curr]);
		pid = fork_them_kids(pipe_fds[!curr], pipe_fds[curr], argv[i], envp);
		i++;
	}
	open_outfile(file_fds, argv[argc-1]);
	pid = fork_them_kids(pipe_fds[curr], file_fds, argv[argc-2], envp);
	// waitpid(pid, &status, 0);
	// wait(&status);
	// if (WIFEXITED(status))
	// 	return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
