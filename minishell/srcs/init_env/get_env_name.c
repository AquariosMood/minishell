/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:48:59 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 23:49:16 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *environ)
{
	char	*name;
	int		i;

	if (!environ)
		return (NULL);
	i = 0;
	while (environ && environ[i] && environ[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (environ && environ[i] && environ[i] != '=')
	{
		name[i] = environ[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}
