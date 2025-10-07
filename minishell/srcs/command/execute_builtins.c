/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:08:46 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/14 10:44:24 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtins(t_minishell *minishell, t_command *current,
		enum e_builtins index_built, int fd_out)
{
	const t_builtin			*builtin;
	static const t_builtin	builtins[7] = {
	{"echo", {.function_fd = ft_echo}, 1},
	{"cd", {.function = ft_cd}, 0},
	{"pwd", {.function_fd = ft_pwd}, 1},
	{"export", {.function_fd = ft_export}, 1},
	{"unset", {.function = ft_unset}, 0},
	{"env", {.function_fd = ft_env}, 1},
	{"exit", {.function = ft_exit}, 0},
	};

	if (index_built >= 7 || !minishell || !current)
		return (FALSE);
	builtin = &builtins[index_built];
	if (builtin && builtin->name == NULL)
		return (FALSE);
	if (!ft_strncmp(current->command, builtin->name,
			ft_strlen(builtin->name)))
	{
		if (builtin && builtin->use_fd)
			return (builtin->func.function_fd(minishell, current, fd_out));
		else
			return (builtin->func.function(minishell, current));
	}
	return (FALSE);
}
