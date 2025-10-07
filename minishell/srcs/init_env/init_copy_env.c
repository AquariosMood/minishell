/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_copy_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:56:04 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 17:04:58 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_one_env(t_copy_env **head, t_copy_env **current, char *environ)
{
	t_copy_env	*create;
	char		*name;
	char		*value;

	name = get_env_name(environ);
	value = get_env_value(environ);
	if (!name || !value)
	{
		free(name);
		free(value);
		return (FALSE);
	}
	create = create_env(name, value, check_is_exported(environ));
	if (!create)
	{
		free(name);
		free(value);
		return (FALSE);
	}
	free(name);
	free(value);
	add_copy_env(head, current, create);
	return (TRUE);
}

t_copy_env	*init_copy_env(char **environ)
{
	t_copy_env	*head;
	t_copy_env	*current;
	int			i;

	if (!environ)
		return (NULL);
	head = NULL;
	current = NULL;
	i = 0;
	while (environ && environ[i])
	{
		if (!init_one_env(&head, &current, environ[i]))
		{
			free_copy_env(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}
