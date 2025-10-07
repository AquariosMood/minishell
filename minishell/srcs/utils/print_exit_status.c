/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:50:36 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/14 13:25:09 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_num_len(int n)
{
	int		len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;

	len = get_num_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	num = n;
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

size_t	handle_exit_status(char **ptr, char *buffer, int exit_status)
{
	char	*exit_status_str;
	size_t	i;

	i = 0;
	(*ptr) += 2;
	exit_status_str = ft_itoa(exit_status);
	while (exit_status_str[i])
	{
		if (buffer)
			buffer[i] = exit_status_str[i];
		i++;
	}
	free(exit_status_str);
	return (i);
}

size_t	size_exit_status(int exit_status)
{
	size_t	size;
	char	*exit_str;

	exit_str = ft_itoa(exit_status);
	if (!exit_str)
		return (0);
	size = ft_strlen(exit_str);
	free(exit_str);
	return (size);
}
