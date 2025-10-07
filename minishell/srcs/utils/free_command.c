/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:05:20 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:08:08 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirect(t_redirect *redirect)
{
	t_redirect	*tmp;

	while (redirect)
	{
		tmp = redirect->next;
		free(redirect->file);
		free(redirect);
		redirect = tmp;
	}
}

void	free_command(t_command *command)
{
	t_command	*tmp;

	while (command)
	{
		tmp = command->next;
		free(command->command);
		free_argv(command->args);
		free_redirect(command->redirect);
		free(command);
		command = tmp;
	}
}
