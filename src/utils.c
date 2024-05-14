/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:30:02 by simon             #+#    #+#             */
/*   Updated: 2024/05/14 15:12:01 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void
	error_exit(
		char *error_message)
{
	ft_printf("Error:\t%s\n", error_message);
	exit(EXIT_FAILURE);
}

void
	free_array(
		void **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

void
	ft_close(
		int *fd)
{
	if (*fd == -1)
		return ;
	if (close(*fd) == -1)
		error_exit(ERR_CLOSE);
	*fd = -1;
}
