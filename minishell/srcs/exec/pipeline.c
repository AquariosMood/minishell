/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 02:17:28 by bryda-si          #+#    #+#             */
/*   Updated: 2025-01-31 02:17:28 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_redirection(t_command_context *context, int index)
{
	if (!context || !context->fd_pipes || !context->number_pipes)
		return ;
	if (index > 0)
		dup2(context->fd_pipes[index - 1][STDIN_FILENO], STDIN_FILENO);
	if (index < context->number_commands - 1)
		dup2(context->fd_pipes[index][STDOUT_FILENO], STDOUT_FILENO);
}

int	try_execute_with_env(char *path, t_command *current, char **env)
{
	execve(path, current->args, env);
	free(path);
	free_array(env);
	return (126);
}

int	try_path_execution(char *path, t_command *current,
	t_minishell *minishell)
{
	char	**env;

	if (access(path, X_OK | R_OK) == 0)
	{
		env = convert_copy_env_to_env(minishell->copy_env);
		if (!env)
		{
			free(path);
			free_minishell(minishell);
			return (1);
		}
		return (try_execute_with_env(path, current, env));
	}
	return (0);
}

int	execute_pipeline_with_redirects(t_minishell *minishell)
{
	int					status;

	if (!init_pipe(minishell, &minishell->context))
		return (1);
	if (execute_pipeline_commands(minishell, &minishell->context))
		return (1);
	close_last_pipe(&minishell->context);
	status = wait_for_children(&minishell->context);
	free_pipe(&minishell->context);
	return (status);
}

int	execute_piped_command(t_minishell *minishell, t_command *current)
{
	char	**paths;
	int		index_builtins;

	if (!minishell || !current || !current->args)
	{
		free_minishell(minishell);
		exit(1);
	}
	index_builtins = return_index_builtins(current);
	if (index_builtins != NO_BUILTINS)
		handle_builtin_execution(minishell, current, index_builtins);
	if (current->command && !current->command[0])
		handle_command_not_found(minishell, current->args[0]);
	paths = split_path(get_path(minishell));
	if (!paths)
	{
		free_minishell(minishell);
		exit(127);
	}
	if (current->args[0] && (current->args[0][0] == '/'
		|| current->args[0][0] == '.'))
		return (handle_absolute_path(current, minishell));
	handle_command_search(minishell, current, paths);
	return (1);
}
