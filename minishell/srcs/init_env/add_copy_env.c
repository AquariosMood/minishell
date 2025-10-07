/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_copy_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:46:28 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 14:25:41 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_copy_env(t_copy_env **head, t_copy_env **current,
	t_copy_env *new_env)
{
	if (!new_env)
		return (FALSE);
	if (!*head)
	{
		*head = new_env;
		*current = new_env;
		return (TRUE);
	}
	else
	{
		(*current)->next = new_env;
		*current = new_env;
		return (TRUE);
	}
}
