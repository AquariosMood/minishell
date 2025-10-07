/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 03:08:33 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-16 03:08:33 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe(t_command_context *context)
{
	int	i;

	if (!context || !context->fd_pipes || context->number_pipes <= 0)
		return ;
	i = 0;
	while (i < context->number_pipes)
	{
		close(context->fd_pipes[i][0]);
		close(context->fd_pipes[i][1]);
		free(context->fd_pipes[i]);
		i++;
	}
	free(context->fd_pipes);
	context->fd_pipes = NULL;
	if (context->pids)
	{
		free(context->pids);
		context->pids = NULL;
	}
	context->number_pipes = 0;
	context->number_commands = 0;
}

void	free_pipe_only(t_command_context *context)
{
	int	i;

	if (!context || !context->fd_pipes)
		return ;
	i = 0;
	while (i < context->number_pipes)
	{
		if (context->fd_pipes[i])
			free(context->fd_pipes[i]);
		i++;
	}
	free(context->fd_pipes);
	context->fd_pipes = NULL;
	if (context->pids)
	{
		free(context->pids);
		context->pids = NULL;
	}
	context->number_pipes = 0;
	context->number_commands = 0;
}
