/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_copy_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 03:28:30 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/07 22:39:12 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_copy_env(t_copy_env *head)
{
	t_copy_env	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("name: %s\n", tmp->name);
		printf("value: %s\n", tmp->value);
		printf("is_exported: %d\n", tmp->is_exported);
		tmp = tmp->next;
	}
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
