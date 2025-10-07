/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 10:10:38 by bryda-si          #+#    #+#             */
/*   Updated: 2025-03-10 10:10:38 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normalize_single_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (!cmd->command && cmd->args && cmd->args[0])
	{
		cmd->command = ft_strdup(cmd->args[0]);
		if (!cmd->command)
			return ;
	}
}

void	normalize_commands(t_command *commands)
{
	t_command	*current;

	current = commands;
	while (current)
	{
		normalize_single_command(current);
		current = current->next;
	}
}
