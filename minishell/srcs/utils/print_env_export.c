/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:11:14 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 15:33:50 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_export(t_copy_env *copy_env, int fd_out)
{
	t_copy_env	*tmp;

	tmp = copy_env;
	if (!tmp)
		return (FALSE);
	while (tmp)
	{
		write(fd_out, "export ", 7);
		write(fd_out, tmp->name, ft_strlen(tmp->name));
		if (tmp->is_exported)
		{
			write(fd_out, "=\"", 2);
			write(fd_out, tmp->value, ft_strlen(tmp->value));
			write(fd_out, "\"\n", 2);
		}
		else
			write(fd_out, "\n", 1);
		tmp = tmp->next;
	}
	return (TRUE);
}
