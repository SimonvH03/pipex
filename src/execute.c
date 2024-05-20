/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:25:26 by simon             #+#    #+#             */
/*   Updated: 2024/05/20 21:22:33 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*
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
	all_paths = ft_split(envp[i] + 5, ':');
	if (all_paths == NULL)
		error_exit(0, command);
	i = 0;
	while (all_paths[i] != NULL)
	{
		path = ft_strjoin_d(all_paths[i], command, '/');
		if (path == NULL)
			error_exit(0, command);
		if (access(path, F_OK) == 0)
			break ;
		ft_free_null(&path);
		i++;
	}
	ft_free_ptr_array((void **)all_paths);
	return (path);
}

void
	execute(
		char *command,
		char **envp)
{
	char	**full_command;
	char	*path;

	full_command = ft_split(command, ' ');
	if (full_command == NULL)
		error_exit(0, command);
	path = select_path(full_command[0], envp);
	if (path == NULL)
		error_exit(127, command);
	execve(path, full_command, envp);
	error_exit(0, command);
}
