/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:50:16 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/08 03:42:46 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *environ)
{
	char	*value;
	int		i;

	if (!environ)
		return (NULL);
	i = 0;
	while (environ && environ[i] && environ[i] != '=')
		i++;
	if (environ && !environ[i])
		return (ft_strdup(""));
	value = ft_strdup(&environ[i + 1]);
	if (!value)
		return (NULL);
	return (value);
}
