/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:48:01 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-09 19:48:01 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command_with_redirects(t_minishell *minishell, t_command *command,
	t_command_context *context, int index)
{
	if (!minishell || !command || !context)
		return (FALSE);
	pipe_redirection(context, index);
	if (!handle_redirections(minishell, command, NO_BUILTINS))
	{
		free_minishell(minishell);
		exit(1);
	}
	close_fd_unused(context, index);
	execute_piped_command(minishell, command);
	return (TRUE);
}

int	execute_pipeline_commands(t_minishell *minishell,
	t_command_context *context)
{
	t_command	*current;
	int			i;

	i = 0;
	current = minishell->commands;
	while (current)
	{
		context->pids[i] = fork();
		if (context->pids[i] == 0)
			execute_command_with_redirects(minishell, current, context, i);
		else if (context->pids[i] < 0)
			return (1);
		close_pipe_fds(context, i);
		current = current->next;
		i++;
	}
	return (0);
}

static int	execute_external_command(t_minishell *minishell, t_command *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (!handle_redirections(minishell, command, NO_BUILTINS))
		{
			free_minishell(minishell);
			exit(1);
		}
		if (!command->command)
		{
			free_minishell(minishell);
			exit(0);
		}
		execute_piped_command(minishell, command);
		exit(1);
	}
	else if (pid < 0)
		return (FALSE);
	waitpid(pid, &status, 0);
	return (check_signum(status));
}

void	dup_and_close(int original_stdout, int original_stdin)
{
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
}

int	execute_single_command_with_redirects(t_minishell *minishell,
	t_command *command)
{
	int		index_builtin;
	int		original_stdout;
	int		original_stdin;

	if (!minishell || !command)
		return (FALSE);
	index_builtin = return_index_builtins(command);
	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	if (index_builtin != NO_BUILTINS)
	{
		if (!handle_redirections(minishell, command, index_builtin))
		{
			dup_and_close(original_stdout, original_stdin);
			return (1);
		}
		execute_builtins(minishell, command, index_builtin, STDOUT_FILENO);
		dup_and_close(original_stdout, original_stdin);
		return (0);
	}
	else
	{
		dup_and_close(original_stdout, original_stdin);
		return (execute_external_command(minishell, command));
	}
}
