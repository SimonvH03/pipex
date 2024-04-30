/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:30:02 by simon             #+#    #+#             */
/*   Updated: 2024/04/30 21:56:37 by simon            ###   ########.fr       */
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

void
	sfree_array(
		void **array,
		size_t ptr_size)
{
	int	i;

	i = 0;
	while(*(array + (ptr_size * i)) != NULL)
	{
		free(*(array + (ptr_size * i)));
		i++;
	}
	free(array);
}
