/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-04 03:32:07 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-04 03:32:07 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_redirection(char *name_file)
{
	(void)name_file;
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, name_file, ft_strlen(name_file));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 2);
}

int	create_or_open_file(char *name_file)
{
	int	fd;

	if (!name_file)
		return (FALSE);
	fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (fd);
	return (fd);
}

int	create_or_append_file(char *name_file)
{
	int	fd;

	if (!name_file)
		return (FALSE);
	fd = open(name_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (fd);
	return (fd);
}

int	redirection_output(t_minishell *minishell, t_redirect *redirect, int fd_out)
{
	char	*name_file;
	int		fd;

	if (!minishell || !redirect || !redirect->file)
		return (FALSE);
	name_file = redirect->file;
	fd = -1;
	if (redirect->type == TOKEN_REDIRECT_OUTPUT)
		fd = create_or_open_file(name_file);
	else if (redirect->type == TOKEN_REDIRECT_APPEND)
		fd = create_or_append_file(name_file);
	if (fd == -1)
	{
		print_error_redirection(name_file);
		return (FALSE);
	}
	else if (dup2(fd, fd_out) == -1)
	{
		print_error_redirection(name_file);
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}
