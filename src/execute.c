/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:25:26 by simon             #+#    #+#             */
/*   Updated: 2024/04/30 20:12:34 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
		sfree_array(command, sizeof(*command));
		error_exit(pid, ERR_PATH);
	}
	execve(path, command, envp);
}
