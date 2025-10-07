/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_copy_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:47:45 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 19:56:11 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_value_in_env(t_copy_env *new_env,
	char *value, char *name, int is_exported)
{
	new_env->name = name;
	new_env->value = value;
	new_env->is_exported = is_exported;
	new_env->next = NULL;
}

t_copy_env	*create_env(char *name, char *value, int is_exported)
{
	t_copy_env	*new_env;
	char		*name_env;
	char		*value_env;

	if (!name || !value)
		return (NULL);
	name_env = ft_strdup(name);
	if (!name_env)
		return (NULL);
	value_env = ft_strdup(value);
	if (!value_env)
	{
		free(name_env);
		return (NULL);
	}
	new_env = malloc(sizeof(t_copy_env));
	if (!new_env)
	{
		free(name_env);
		free(value_env);
		return (NULL);
	}
	push_value_in_env(new_env, value_env, name_env, is_exported);
	return (new_env);
}
