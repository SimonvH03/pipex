/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:25:26 by simon             #+#    #+#             */
/*   Updated: 2024/05/01 21:18:33 by svan-hoo         ###   ########.fr       */
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
		return (NULL);
	i = 0;
	while (all_paths[i] != NULL)
	{
		path = ft_strjoin_d(all_paths[i], command, '/');
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_array((void **)all_paths);
	return (NULL);
}

void
	execute(
		char *argument,
		char **envp)
{
	char	**full_command;
	char	*path;

	full_command = ft_split(argument, ' ');
	if (full_command == NULL)
		error_exit(ERR_MALLOC);
	path = select_path(full_command[0], envp);
	if (path == NULL)
	{
		ft_printf("%s:\t", argument);
		free_array((void **)full_command);
		error_exit(ERR_PATH);
	}
	execve(path, full_command, envp);
}
