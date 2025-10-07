/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-28 22:42:40 by bryda-si          #+#    #+#             */
/*   Updated: 2025-01-28 22:42:40 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_absolute_path(t_command *current, t_minishell *minishell)
{
	struct stat	stats;

	if (stat(current->args[0], &stats) < 0)
	{
		handle_not_found_error(minishell, current->args[0]);
		exit(127);
	}
	if (S_ISDIR(stats.st_mode))
		handle_directory_error(minishell, current->args[0]);
	if (S_ISREG(stats.st_mode))
	{
		if (access(current->args[0], X_OK | R_OK) == 0)
			execve(current->args[0], current->args,
				convert_copy_env_to_env(minishell->copy_env));
		else
			handle_permission_error(minishell, current->args[0]);
	}
	handle_not_found_error(minishell, current->args[0]);
	exit(127);
}

int	try_execute_command(char *path, t_command *current,
	t_minishell *minishell)
{
	char	**tmp_env;

	if (access(path, X_OK | R_OK) == 0)
	{
		tmp_env = convert_copy_env_to_env(minishell->copy_env);
		if (!tmp_env)
			return (FALSE);
		if (execve(path, current->args, tmp_env) == -1)
		{
			free(path);
			free_tokens(minishell->tokens);
			free_command(current);
			free_copy_env(minishell->copy_env);
			free_array(tmp_env);
			exit(126);
		}
	}
	return (0);
}

char	*get_and_check_path(char **paths, int i, t_command *current)
{
	char	*path;

	path = join_full_path(paths[i], current);
	if (!path)
		return (NULL);
	return (path);
}

int	handle_path_execution(t_command *current, t_minishell *minishell)
{
	char	**paths;
	char	*path;
	int		i;

	paths = split_path(get_path(minishell));
	if (!paths)
	{
		handle_not_found_error(minishell, current->args[0]);
		return (127);
	}
	i = 0;
	while (paths[i])
	{
		path = get_and_check_path(paths, i, current);
		if (!path)
			return (free_array(paths), 127);
		if (try_execute_command(path, current, minishell) == -1)
			return (free_array(paths), 126);
		free(path);
		i++;
	}
	free_array(paths);
	handle_command_not_found(minishell, current->args[0]);
	return (127);
}

int	exec(t_minishell *minishell, t_command *current)
{
	int	status;
	int	pid;

	if (!minishell || !current || !minishell->copy_env)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (current->command && !current->command[0])
			handle_command_not_found(minishell, current->args[0]);
		if (current->args[0][0] == '/' || current->args[0][0] == '.')
			exit(handle_absolute_path(current, minishell));
		exit(handle_path_execution(current, minishell));
	}
	waitpid(pid, &status, 0);
	return (check_signum(status));
}
