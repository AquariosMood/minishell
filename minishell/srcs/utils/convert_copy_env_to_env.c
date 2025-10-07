/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_copy_env_to_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:09:41 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 15:29:53 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_env(t_copy_env *copy_env)
{
	char	*env;
	char	*name;
	char	*value;

	if (!copy_env)
		return (NULL);
	name = ft_strjoin(copy_env->name, "=");
	value = ft_strjoin(name, copy_env->value);
	if (!name || !value)
		return (NULL);
	env = ft_strdup(value);
	free(name);
	free(value);
	return (env);
}

char	**convert_copy_env_to_env(t_copy_env *copy_env)
{
	t_copy_env	*tmp;
	char		**env;
	int			i;

	i = 0;
	tmp = copy_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	tmp = copy_env;
	while (tmp)
	{
		env[i] = set_env(tmp);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
