/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:30:02 by simon             #+#    #+#             */
/*   Updated: 2024/04/30 20:07:35 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void
	error_exit(
		pid_t pid,
		char *error_message)
{
	ft_printf("Error:\tpid %d:\t%s\n", pid, error_message);
	exit(EXIT_FAILURE);
}
