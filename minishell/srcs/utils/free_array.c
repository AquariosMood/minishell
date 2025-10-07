/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 22:18:23 by bryda-si          #+#    #+#             */
/*   Updated: 2025-01-30 22:18:23 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (FALSE);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (TRUE);
}
