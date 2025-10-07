/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:13:42 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/14 10:39:06 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(t_minishell *minishell)
{
	minishell->interactive = INTERACTIVE;
	minishell->tokens = NULL;
	minishell->exit_code = 0;
	minishell->commands = NULL;
	minishell->context = (t_command_context){0};
	minishell->copy_env = init_copy_env(environ);
	if (!minishell->copy_env)
		return (FALSE);
	return (TRUE);
}

int	init_all_struct_minishell(t_minishell *minishell)
{
	if (!init_minishell(minishell))
	{
		free_copy_env(minishell->copy_env);
		return (FALSE);
	}
	if (!init_signal())
	{
		free_copy_env(minishell->copy_env);
		return (FALSE);
	}
	return (TRUE);
}
