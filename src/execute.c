/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:25:26 by simon             #+#    #+#             */
/*   Updated: 2024/04/30 22:35:55 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*
	select_path(
		char *command,
		char **envp)
{
	char	*path;
	char	**all_paths;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	ft_printf("%s\n", envp[i]);
	return (NULL);
}

void
	execute(
		pid_t pid,
		char *argument,
		char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(argument, ' ');
	if (command == NULL)
		error_exit(pid, ERR_MALLOC);
	path = select_path(command[0], envp);
	if (path == NULL)
	{
		sfree_array((void **)command, sizeof(char *));
		error_exit(pid, ERR_PATH);
	}
	execve(path, command, envp);
}
