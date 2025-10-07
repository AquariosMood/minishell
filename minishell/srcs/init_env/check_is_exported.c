/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_exported.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:50:55 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 15:04:27 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_exported(char *environ)
{
	int	i;

	if (!environ)
		return (FALSE);
	i = 0;
	while (environ && environ[i])
	{
		if (environ[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
