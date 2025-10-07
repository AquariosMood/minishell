/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:50:36 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/02 09:49:58 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_args(char **args)
{
	char	**new_args;
	int		i;

	i = 0;
	while (args && args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (args && args[i])
	{
		new_args[i] = ft_strdup(args[i]);
		if (new_args && !new_args[i])
		{
			free_argv(new_args);
			return (NULL);
		}
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}

t_command	*create_command(char *command, char **args, int index_command)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	if (command[0] == '<' || command[0] == '>')
		new_command->command = NULL;
	else
	{
		new_command->command = ft_strdup(command);
		if (!new_command->command)
			return (free(new_command), NULL);
	}
	new_command->args = copy_args(args);
	if (new_command && !new_command->args)
	{
		free(new_command->command);
		free(new_command);
		return (NULL);
	}
	free_argv(args);
	new_command->index = index_command;
	new_command->redirect = NULL;
	new_command->next = NULL;
	return (new_command);
}
