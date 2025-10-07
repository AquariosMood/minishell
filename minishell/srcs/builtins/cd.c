/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:22:34 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/10 16:02:05 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_and_replace_env(t_copy_env *copy_env, char *old_pwd, char *pwd)
{
	t_copy_env	*tmp;

	tmp = copy_env;
	if (!old_pwd || !pwd)
		return (FALSE);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = old_pwd;
			if (!tmp->value)
				return (FALSE);
		}
		else if (ft_strcmp(tmp->name, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = pwd;
			if (!tmp->value)
				return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

int	change_directory_env(char *old_pwd, t_copy_env *copy_env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!old_pwd || !pwd)
		return (free(pwd), free(old_pwd), FALSE);
	if (!free_and_replace_env(copy_env, old_pwd, pwd))
		return (free(pwd), free(old_pwd), FALSE);
	return (TRUE);
}

static void	print_cd_error(char *arg, char *message)
{
	write(2, "minishell: cd: ", 15);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

static void	print_chdir_error(char *arg)
{
	write(2, "minishell: chdir: error retrieving current directory ", 54);
	write(2, ": getcwd: cannot access parent directories: ", 44);
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

int	ft_cd(t_minishell *minishell, t_command *command)
{
	char	*old_pwd;

	if (!command || !command->args[1])
		return (FALSE);
	if (command->args[2])
	{
		minishell->exit_code = 1;
		write(2, "minishell: cd: too many arguments\n", 34);
		return (FALSE);
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		print_chdir_error("No such file or directory");
		minishell->exit_code = 1;
	}
	if (chdir(command->args[1]) == -1)
	{
		print_cd_error(command->args[1], "No such file or directory");
		minishell->exit_code = 1;
		return (free(old_pwd), FALSE);
	}
	minishell->exit_code = 0;
	change_directory_env(old_pwd, minishell->copy_env);
	return (TRUE);
}
