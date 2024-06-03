/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:25:26 by simon             #+#    #+#             */
/*   Updated: 2024/06/03 21:23:12 by svan-hoo         ###   ########.fr       */
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
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (ft_strjoin_d(".", command, '/'));
	all_paths = ft_split(envp[i] + 5, ':');
	if (all_paths == NULL)
		error_exit(errno, command);
	i = 0;
	while (all_paths[i] != NULL)
	{
		path = ft_strjoin_d(all_paths[i], command, '/');
		if (path == NULL)
			error_exit(errno, command);
		if (access(path, F_OK) == 0)
			break ;
		ft_free_null(&path);
		i++;
	}
	ft_free_ptr_array((void **)all_paths);
	return (path);
}

// void
// 	execute(
// 		char *command,
// 		char **envp)
// {
// 	char	**full_command;
// 	char	*path;

// 	full_command = ft_split(command, ' ');
// 	if (full_command == NULL)
// 		error_exit(errno, command);
// 	if (command[0] == '/'
// 		|| command[0] == '.'
// 		|| command[0] == '~')
// 		path = command;
// 	else
// 		path = select_path(full_command[0], envp);
// 	if (path == NULL)
// 		error_exit(127, command);
// 	execve(path, full_command, envp);
// 	if (!(command[0] == '/'
// 			|| command[0] == '.'
// 			|| command[0] == '~')
// 		&& access(command, X_OK) == -1)
// 		error_exit(127, command);
// 	error_exit(errno, command);
// }

void
	execute(
		char *command,
		char **envp)
{
	char	**full_command;
	char	*path;

	full_command = ft_split(command, ' ');
	if (full_command == NULL)
		error_exit(errno, command);
	if (command[0] == '/'
		|| command[0] == '.'
		|| command[0] == '~')
	{
		execve(command, full_command, envp);
	}
	else
	{
		path = select_path(full_command[0], envp);
		if (path == NULL)
			error_exit(127, command);
		execve(path, full_command, envp);
		if (access(command, X_OK) == -1)
			error_exit(127, command);
	}
	error_exit(errno, command);
}
