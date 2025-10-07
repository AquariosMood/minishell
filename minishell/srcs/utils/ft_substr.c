/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:37:53 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:07:03 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *str, int i)
{
	int		j;
	char	*substr;

	j = 0;
	substr = malloc(sizeof(char) * (i + 1));
	if (!substr)
		return (NULL);
	while (j < i)
	{
		substr[j] = str[j];
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
