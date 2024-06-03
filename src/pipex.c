/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/03 21:28:11 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int
	zombie_prevention_protocol(
		int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		error_exit(errno, NULL);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
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
