/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-05 01:57:55 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-05 01:57:55 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input_file(t_minishell *minishell, char *name_file)
{
	int	fd;

	if (!minishell || !name_file)
		return (FALSE);
	fd = open(name_file, O_RDONLY);
	if (fd == -1)
		return (fd);
	return (fd);
}

int	redirect_input(t_minishell *minishell, t_redirect *redirect,
	int index_builtin)
{
	char	*name_file;
	int		fd;

	(void)index_builtin;
	if (!minishell || !redirect || !redirect->file)
		return (FALSE);
	name_file = redirect->file;
	fd = redirect_input_file(minishell, name_file);
	if (fd == -1)
	{
		print_error_redirection(name_file);
		return (FALSE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		print_error_redirection(name_file);
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}
