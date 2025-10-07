/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:29:45 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:07:33 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *str, unsigned int end)
{
	unsigned int	i;
	char			*new_str;

	new_str = malloc(sizeof(char) * (end + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < end)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
