/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:43 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/01 00:16:51 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "stdio.h"
# include "wait.h"

# define ERR_OPEN	"Open"
# define ERR_CLOSE	"Close"
# define ERR_PIPE	"Pipe"
# define ERR_MALLOC	"Malloc"
# define ERR_ARGS	"Bad Arguments"
# define ERR_PATH	"Failed to find Path"
# define ERR_EXIT	"Forked Process failed to Exit"

// file: execute.c
void	execute(pid_t pid, char *argument, char **envp);

// file: utils.c
void	error_exit(pid_t pid, char *error_message);
void	sfree_array(void **array, size_t ptr_size);

#endif