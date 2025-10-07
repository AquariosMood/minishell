/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:46:52 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:21:31 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s_join;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	s_join = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)
			* sizeof(char));
	if (!s_join)
		return (NULL);
	i = 0;
	while (*s1)
	{
		s_join[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		s_join[i] = *s2++;
		i++;
	}
	s_join[i] = '\0';
	return (s_join);
}
