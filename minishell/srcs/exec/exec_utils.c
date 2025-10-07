/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-14 00:39:22 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-14 00:39:22 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	template_handle_error(t_minishell *minishell, char *arg,
	char *error_message, int exit_code)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	free_minishell(minishell);
	minishell->context = (t_command_context){0};
	exit(exit_code);
}

void	handle_directory_error(t_minishell *minishell, char *arg)
{
	template_handle_error(minishell, arg, ": Is a directory\n", 126);
}

void	handle_permission_error(t_minishell *minishell, char *arg)
{
	template_handle_error(minishell, arg, ": Permission denied\n", 126);
}

void	handle_not_found_error(t_minishell *minishell, char *arg)
{
	template_handle_error(minishell, arg, ": No such file or directory\n", 127);
}

void	handle_command_not_found(t_minishell *minishell, char *arg)
{
	template_handle_error(minishell, arg, ": command not found\n", 127);
}
