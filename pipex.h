/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex copy.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:43 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/29 15:28:38 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <wait.h>
# include <errno.h>
# include <string.h>

// file: fork_some.c
int		fork_up_the_first_one(
			char *infile,
			char *command,
			char **envp);
int		fork_them_kids(
			int input_fd,
			char *command,
			char **envp);
int		favourite_child(
			int input_fd,
			char *outfile,
			char *command,
			char **envp);

// file: execute.c
void	execute(
			char *command,
			char **envp);

// file: utils.c
void	error_exit(int i, char *param);
void	set_input(int input_fd);
void	set_output(int output_fd);
int		open_infile(char *infile);
int		open_outfile(char *outfile);

#endif