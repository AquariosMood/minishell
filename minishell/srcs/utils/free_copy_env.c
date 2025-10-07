/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_copy_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 03:01:30 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 19:54:26 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_copy_env(t_copy_env *head)
{
	t_copy_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = tmp;
	}
}
