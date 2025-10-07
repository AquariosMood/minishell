/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:34:19 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/14 10:45:34 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_name_builtins(enum e_builtins index_built)
{
	static char	*name_built[8];

	name_built[0] = "echo";
	name_built[1] = "cd";
	name_built[2] = "pwd";
	name_built[3] = "export";
	name_built[4] = "unset";
	name_built[5] = "env";
	name_built[6] = "exit";
	name_built[7] = NULL;
	return (name_built[index_built]);
}

int	return_index_builtins(t_command *commands)
{
	enum e_builtins	index_built[8];
	char			*name_built;
	int				i;

	index_built[0] = ECHO;
	index_built[1] = CD;
	index_built[2] = PWD;
	index_built[3] = EXPORT;
	index_built[4] = UNSET;
	index_built[5] = ENV;
	index_built[6] = EXIT;
	index_built[7] = NO_BUILTINS;
	i = 0;
	if (!commands || !commands->command)
		return (NO_BUILTINS);
	while (index_built[i] != NO_BUILTINS)
	{
		name_built = return_name_builtins(index_built[i]);
		if (ft_strncmp(commands->command, name_built,
				ft_strlen(name_built)) == 0)
			return (index_built[i]);
		i++;
	}
	return (NO_BUILTINS);
}

void	execute_command(t_minishell *minishell, int fd_out)
{
	t_command	*current;
	int			index_built;

	if (!minishell->commands || !minishell->commands->command)
		return ;
	current = minishell->commands;
	while (current)
	{
		index_built = return_index_builtins(current);
		if (index_built != NO_BUILTINS)
			execute_builtins(minishell, current, index_built, fd_out);
		else
			minishell->exit_code = exec(minishell, current);
		current = current->next;
	}
}
