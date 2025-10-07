/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:46:55 by bryda-si          #+#    #+#             */
/*   Updated: 2024/05/23 17:34:50 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr_src;

	if (!dest && !src)
		return (NULL);
	ptr = (unsigned char *) dest;
	ptr_src = (unsigned char *) src;
	while (n--)
		*ptr++ = *ptr_src++;
	return (dest);
}
