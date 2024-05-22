/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:51:43 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/22 22:59:48 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <wait.h>
# include <errno.h>
#include <string.h>

// file: execute.c
void	execute(char *command, char **envp);

// file: utils.c
void	error_exit(int i, char *param);
void	set_input(int input_fd);
void	set_output(int output_fd);
int		open_infile(char *infile);
int		open_outfile(char *outfile);

#endif