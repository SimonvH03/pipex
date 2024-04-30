/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:25:26 by simon             #+#    #+#             */
/*   Updated: 2024/05/01 00:17:11 by simon            ###   ########.fr       */
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
	// sfree_array((void **)all_paths, sizeof (char *));
	return (NULL);
}

void
	execute(
		pid_t pid,
		char *argument,
		char **envp)
{
	char	**full_command;
	char	*path;

	full_command = ft_split(argument, ' ');
	if (full_command == NULL)
		error_exit(pid, ERR_MALLOC);
	path = select_path(full_command[0], envp);
	if (path == NULL)
	{
		// sfree_array((void **)full_command, sizeof(char *));
		error_exit(pid, ERR_PATH);
	}
	execve(path, full_command, envp);
}
