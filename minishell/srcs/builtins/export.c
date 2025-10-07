/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:30 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 20:13:34 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_copy_env *copy_env, char *arg)
{
	t_copy_env	*tmp;

	if (!copy_env || !arg)
		return (FALSE);
	tmp = copy_env;
	if (check_existing_env(tmp, arg))
		return (update_env_existing(tmp, arg, check_is_exported(arg)));
	else
		return (add_new_env(tmp, arg));
}

int	ft_export(t_minishell *minishell, t_command *command, int fd_out)
{
	t_copy_env	*tmp;
	char		*arg;
	int			i;

	if (!minishell || !command)
		return (FALSE);
	if (!command->args[1])
	{
		if (!print_env_export(minishell->copy_env, fd_out))
			return (FALSE);
		return (TRUE);
	}
	tmp = minishell->copy_env;
	i = 1;
	while (command->args[i])
	{
		if (!check_name_export(minishell, command->args[i]))
			return (print_error_builtins("export", ERROR_EXPORT), FALSE);
		arg = command->args[i];
		if (!export(tmp, arg))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
