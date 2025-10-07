/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-14 02:40:03 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-14 02:40:03 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_fds(t_command_context *context, int i)
{
	if (i > 0)
	{
		close(context->fd_pipes[i - 1][0]);
		close(context->fd_pipes[i - 1][1]);
	}
}

void	close_last_pipe(t_command_context *context)
{
	if (!context || !context->fd_pipes || context->number_pipes <= 0)
		return ;
	if (context->number_pipes > 0)
	{
		close(context->fd_pipes[context->number_pipes - 1][0]);
		close(context->fd_pipes[context->number_pipes - 1][1]);
	}
}

int	wait_for_children(t_command_context *context)
{
	int		status;
	pid_t	wait_result;
	int		last_status;
	int		i;

	i = 0;
	status = 0;
	while (i < context->number_commands)
	{
		wait_result = waitpid(context->pids[i], &status, 0);
		if (wait_result == -1)
			perror("waitpid");
		else
		{
			last_status = status;
			if (WIFSIGNALED(status))
				if (WTERMSIG(status) == SIGINT && g_sigint_received)
					g_sigint_received = 0;
		}
		i++;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	return (check_signum(last_status));
}

void	unlink_heredoc_files(t_redirect *redirect)
{
	t_redirect	*tmp;

	if (!redirect)
		return ;
	tmp = redirect;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
			unlink(tmp->file);
		tmp = tmp->next;
	}
}

int	handle_redirections(t_minishell *minishell, t_command *command,
	int index_builtin)
{
	t_redirect	*redirect;

	if (!command)
		return (FALSE);
	if (!command->redirect)
		return (TRUE);
	redirect = command->redirect;
	while (redirect)
	{
		if (redirect->type == TOKEN_REDIRECT_INPUT
			|| redirect->type == TOKEN_HEREDOC)
		{
			if (!redirect_input(minishell, redirect, index_builtin))
				return (unlink_heredoc_files(command->redirect), FALSE);
		}
		else if (redirect->type == TOKEN_REDIRECT_OUTPUT
			|| redirect->type == TOKEN_REDIRECT_APPEND)
		{
			if (!redirection_output(minishell, redirect, STDOUT_FILENO))
				return (unlink_heredoc_files(command->redirect), FALSE);
		}
		redirect = redirect->next;
	}
	unlink_heredoc_files(command->redirect);
	return (TRUE);
}
