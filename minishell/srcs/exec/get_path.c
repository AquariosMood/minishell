/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-28 19:19:44 by bryda-si          #+#    #+#             */
/*   Updated: 2025-01-28 19:19:44 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_minishell *minishell)
{
	t_copy_env	*tmp_env;

	if (!minishell || !minishell->commands || !minishell->copy_env)
		return (NULL);
	tmp_env = minishell->copy_env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->name, "PATH") == 0)
			return (tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	**split_path(char *path)
{
	char	**paths;

	if (!path || !*path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (free_array(paths), NULL);
	return (paths);
}

char	*join_full_path(char *path, t_command *commands)
{
	size_t	i;
	size_t	j;
	char	*full_path;

	if (!path || !commands || !commands->command)
		return (NULL);
	i = 0;
	j = 0;
	full_path = malloc((ft_strlen(path) + ft_strlen(commands->command) + 2)
			* sizeof(char));
	if (!full_path)
		return (NULL);
	while (path[i])
		full_path[j++] = path[i++];
	full_path[j++] = '/';
	i = 0;
	while (commands->command[i])
		full_path[j++] = commands->command[i++];
	full_path[j] = '\0';
	return (full_path);
}
