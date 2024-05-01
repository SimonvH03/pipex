/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:43 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/01 21:22:21 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "stdio.h"
# include "stdbool.h"
# include "wait.h"

# define ERR_OPEN	"Open"
# define ERR_CLOSE	"Close"
# define ERR_PIPE	"Pipe"
# define ERR_MALLOC	"Malloc"
# define ERR_ARGS	"Bad Arguments"
# define ERR_PATH	"Failed to find Path"
# define ERR_EXIT	"Forked Process failed to Exit"

// file: execute.c
void	execute(char *argument, char **envp);

// file: utils.c
void	error_exit(char *error_message);
void	free_array(void **array);
void	ft_close(int *fd);

#endif