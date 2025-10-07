/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:31:52 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/05 02:56:14 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_minishell *minishell, t_command *command, int fd_out)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		write(2, "minishell: pwd: error retrieving current directory ", 50);
		write(2, ": getcwd: cannot access parent directories: ", 44);
		write(2, "No such file or directory\n", 27);
		minishell->exit_code = 1;
		return (FALSE);
	}
	(void)minishell;
	(void)command;
	write(fd_out, path, ft_strlen(path));
	write(fd_out, "\n", 1);
	free(path);
	return (TRUE);
}
