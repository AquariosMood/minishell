/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:50:03 by bryda-si          #+#    #+#             */
/*   Updated: 2024/11/30 10:06:09 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->tokens)
	{
		free_tokens(minishell->tokens);
		minishell->tokens = NULL;
	}
	if (minishell->commands)
	{
		free_command(minishell->commands);
		minishell->commands = NULL;
	}
	if (minishell->copy_env)
	{
		free_copy_env(minishell->copy_env);
		minishell->copy_env = NULL;
	}
	if (&minishell->context != (t_command_context *)0)
	{
		free_pipe(&minishell->context);
		minishell->context = (t_command_context){NULL, NULL, 0, 0};
	}
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
}
