/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 14:48:21 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-22 14:48:21 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_filename_and_id(char *prefix, unsigned int command_index,
	unsigned int redir_index)
{
	char	*redirection_str;
	char	*command_str;
	char	*result;
	char	*tmp;

	command_str = ft_itoa(command_index);
	if (!command_str)
		return (NULL);
	redirection_str = ft_itoa(redir_index);
	if (!redirection_str)
		return (free(command_str), NULL);
	tmp = ft_strjoin(prefix, command_str);
	free(command_str);
	if (!tmp)
		return (free(redirection_str), NULL);
	result = ft_strjoin(tmp, "-");
	free(tmp);
	if (!result)
		return (free(redirection_str), NULL);
	tmp = ft_strjoin(result, redirection_str);
	free(result);
	free(redirection_str);
	return (tmp);
}

static int	process_heredoc_iteration(int fd, char *delimiter,
	t_minishell *minishell)
{
	char	*line;
	int		ret;

	line = read_line_from_fd(STDIN_FILENO);
	if (g_sigint_received || !line)
	{
		if (line)
			free(line);
		write(STDOUT_FILENO, "\n", 1);
		return (FALSE);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (TRUE);
	}
	ret = write_line_to_fd(fd, line, minishell);
	free(line);
	if (!ret)
		return (FALSE);
	return (2);
}

int	loop_heredoc(int fd, char *delimiter, t_minishell *minishell)
{
	struct sigaction	act;
	struct sigaction	act2;
	int					original_stdin;
	int					iteration_result;

	setup_heredoc_signals(&act, &act2);
	disable_echoctl();
	original_stdin = dup(STDIN_FILENO);
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		if (g_sigint_received)
			return (handle_heredoc_cleanup(&act2, original_stdin, NULL));
		iteration_result = process_heredoc_iteration(fd, delimiter, minishell);
		if (iteration_result == FALSE)
			return (handle_heredoc_cleanup(&act2, original_stdin, NULL));
		if (iteration_result == TRUE)
			break ;
	}
	return (handle_heredoc_cleanup(&act2, original_stdin, NULL));
}

int	handle_heredoc(t_command *command, t_redirect *redirect,
	t_minishell *minishell)
{
	char	*temp_filename;
	char	*delimiter;
	int		fd;

	if (!command || !redirect)
		return (FALSE);
	delimiter = redirect->file;
	temp_filename = join_filename_and_id("/tmp/minishell_heredoc_",
			command->index, redirect->index);
	if (!temp_filename)
		return (FALSE);
	fd = open(temp_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		unlink(temp_filename);
		return (free(temp_filename), FALSE);
	}
	if (!loop_heredoc(fd, delimiter, minishell))
	{
		unlink(temp_filename);
		return (free(temp_filename), close(fd), FALSE);
	}
	free(delimiter);
	redirect->file = temp_filename;
	return (close(fd), TRUE);
}

int	init_heredoc(t_command *command, t_minishell *minishell)
{
	t_redirect	*redirect_tmp;
	t_command	*command_tmp;

	if (!command || !command->redirect)
		return (TRUE);
	command_tmp = command;
	while (command_tmp)
	{
		redirect_tmp = command_tmp->redirect;
		while (redirect_tmp)
		{
			if (redirect_tmp->type == TOKEN_HEREDOC)
				if (!handle_heredoc(command_tmp, redirect_tmp, minishell))
					return (FALSE);
			redirect_tmp = redirect_tmp->next;
		}
		command_tmp = command_tmp->next;
	}
	return (TRUE);
}
