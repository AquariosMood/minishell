/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 02:24:00 by bryda-si          #+#    #+#             */
/*   Updated: 2025-01-31 02:24:00 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	if (!tokens)
		return (FALSE);
	tmp = tokens;
	i = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	init_context(t_minishell *minishell, t_command_context *context)
{
	if (!minishell || !context)
		return (FALSE);
	context->number_commands = count_pipe(minishell->tokens) + 1;
	context->number_pipes = context->number_commands - 1;
	context->pids = malloc(context->number_commands * sizeof(pid_t));
	if (!context->pids)
		return (FALSE);
	context->fd_pipes = malloc(context->number_pipes * sizeof(int *));
	if (!context->fd_pipes)
		return (free(context->pids), FALSE);
	return (TRUE);
}

int	create_pipe(t_command_context *context)
{
	int	i;

	i = 0;
	while (i < context->number_pipes)
	{
		context->fd_pipes[i] = malloc(2 * sizeof(int));
		if (!context->fd_pipes[i] || pipe(context->fd_pipes[i]) == -1)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	init_pipe(t_minishell *minishell, t_command_context *context)
{
	if (!minishell || !minishell->commands || !context)
		return (FALSE);
	if (!init_context(minishell, context))
		return (FALSE);
	if (!create_pipe(context))
		return (FALSE);
	return (TRUE);
}
