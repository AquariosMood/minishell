/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-14 03:01:47 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-14 03:01:47 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin_execution(t_minishell *minishell, t_command *current,
	int index_builtins)
{
	signal(SIGPIPE, SIG_IGN);
	execute_builtins(minishell, current, index_builtins, STDOUT_FILENO);
	close_last_pipe(&minishell->context);
	free_minishell(minishell);
	minishell->context = (t_command_context){0};
	exit(minishell->exit_code);
}

void	handle_command_search(t_minishell *minishell, t_command *current,
	char **paths)
{
	char	*path;
	int		exec_result;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = join_full_path(paths[i], current);
		if (!path)
		{
			free_array(paths);
			free_minishell(minishell);
			exit(127);
		}
		exec_result = try_path_execution(path, current, minishell);
		if (exec_result > 0)
		{
			free_minishell(minishell);
			exit(exec_result);
		}
		free(path);
		i++;
	}
	free_array(paths);
	handle_command_not_found(minishell, current->args[0]);
}

void	close_fd_unused(t_command_context *context, int index)
{
	int	i;

	i = 0;
	(void)index;
	while (i < context->number_pipes)
	{
		close(context->fd_pipes[i][0]);
		close(context->fd_pipes[i][1]);
		i++;
	}
}
