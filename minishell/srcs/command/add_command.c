/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:50:16 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 15:02:35 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command(t_command **head, t_command **current,
	t_command *new_command)
{
	if (!new_command)
		return ;
	if (!*head)
	{
		*head = new_command;
		*current = new_command;
	}
	else
	{
		(*current)->next = new_command;
		*current = new_command;
	}
}
