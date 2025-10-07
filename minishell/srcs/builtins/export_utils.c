/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-14 00:14:12 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-14 00:14:12 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name_export(t_minishell *minishell, char *str)
{
	int	i;

	i = 0;
	if (!str || !check_one_char_value_env(str[i]))
	{
		minishell->exit_code = 1;
		return (FALSE);
	}
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!check_one_char_value_env(str[i]) && !ft_isdigit(str[i]))
		{
			minishell->exit_code = 1;
			return (FALSE);
		}
		i++;
	}
	minishell->exit_code = 0;
	return (TRUE);
}

int	check_existing_env(t_copy_env *copy_env, char *value)
{
	t_copy_env	*tmp;
	char		*name;

	if (!copy_env)
		return (FALSE);
	tmp = copy_env;
	name = get_env_name(value);
	if (!name)
		return (FALSE);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (free(name), TRUE);
		tmp = tmp->next;
	}
	return (free(name), FALSE);
}

int	add_new_env(t_copy_env *copy_env, char *value)
{
	t_copy_env	*new_env;
	t_copy_env	*tmp;
	char		*name;
	char		*value_name;

	if (!copy_env)
		return (FALSE);
	name = get_env_name(value);
	value_name = get_env_value(value);
	if (!name || !value)
		return (free(name), free(value_name), FALSE);
	new_env = create_env(name, value_name, check_is_exported(value));
	free(name);
	free(value_name);
	if (!new_env)
		return (FALSE);
	tmp = copy_env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
	return (TRUE);
}

int	update_env_existing(t_copy_env *copy_env, char *value, int is_exported)
{
	t_copy_env	*tmp;
	char		*name;

	if (!copy_env)
		return (FALSE);
	tmp = copy_env;
	while (tmp)
	{
		name = get_env_name(value);
		if (ft_strcmp(tmp->name, name) == 0)
		{
			if (is_exported == 0)
				return (free(name), TRUE);
			free(tmp->value);
			free(name);
			tmp->value = get_env_value(value);
			tmp->is_exported = is_exported;
			return (TRUE);
		}
		free(name);
		tmp = tmp->next;
	}
	return (FALSE);
}
