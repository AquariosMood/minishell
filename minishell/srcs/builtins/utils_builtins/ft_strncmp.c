/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:41:38 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:21:42 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*n_s1;
	unsigned char	*n_s2;
	size_t			i;

	if (n == 0)
		return (0);
	n_s1 = (unsigned char *) s1;
	n_s2 = (unsigned char *) s2;
	i = 0;
	while ((n_s1[i] == n_s2[i] && n_s1[i] && n_s2[i]) && i < n - 1)
		i++;
	return (n_s1[i] - n_s2[i]);
}
