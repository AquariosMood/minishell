/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:58:50 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/09 17:11:13 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_env(t_copy_env **copy_env, char *arg)
{
	t_copy_env	*tmp;
	t_copy_env	*prev;

	if (!copy_env || !*copy_env || !arg)
		return (FALSE);
	tmp = *copy_env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, arg) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*copy_env = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return (TRUE);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (FALSE);
}

int	ft_unset(t_minishell *minishell, t_command *command)
{
	t_copy_env	*tmp_env;
	int			i;

	if (!minishell || !command || !command->args[1])
		return (FALSE);
	tmp_env = minishell->copy_env;
	if (!tmp_env)
		return (FALSE);
	i = 1;
	while (command->args[i])
	{
		if (check_existing_env(tmp_env, command->args[i]))
			delete_env(&minishell->copy_env, command->args[i]);
		i++;
	}
	return (TRUE);
}
