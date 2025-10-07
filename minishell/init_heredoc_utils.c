/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-01 14:06:10 by bryda-si          #+#    #+#             */
/*   Updated: 2025-03-01 14:06:10 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		enable_echoctl();
		g_sigint_received = 1;
		close(STDIN_FILENO);
	}
}

void	setup_heredoc_signals(struct sigaction *act, struct sigaction *act2)
{
	struct sigaction	ignore_sig;

	g_sigint_received = 0;
	act->sa_handler = heredoc_signal_handler;
	act->sa_flags = 0;
	sigemptyset(&act->sa_mask);
	sigaction(SIGINT, act, act2);
	ignore_sig.sa_handler = SIG_IGN;
	ignore_sig.sa_flags = 0;
	sigemptyset(&ignore_sig.sa_mask);
	sigaction(SIGQUIT, &ignore_sig, NULL);
}

char	*expand_heredoc(t_minishell *minishell, char *line)
{
	size_t	new_length;
	char	*expanded;

	new_length = expand_heredoc_length(minishell, line);
	expanded = malloc(new_length + 1);
	if (!expanded)
		return (NULL);
	fill_expanded_heredoc(minishell, line, expanded);
	return (expanded);
}

int	write_line_to_fd(int fd, char *line, t_minishell *minishell)
{
	char	*expanded_line;

	expanded_line = expand_heredoc(minishell, line);
	if (!expanded_line)
		return (FALSE);
	if (write(fd, expanded_line, ft_strlen(expanded_line)) == -1)
	{
		free(expanded_line);
		return (FALSE);
	}
	if (write(fd, "\n", 1) == -1)
	{
		free(expanded_line);
		return (FALSE);
	}
	free(expanded_line);
	return (TRUE);
}

int	handle_heredoc_cleanup(struct sigaction *act2,
	int original_stdin, char *line)
{
	(void)line;
	sigaction(SIGINT, act2, NULL);
	enable_echoctl();
	if (original_stdin >= 0)
	{
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
	}
	if (g_sigint_received)
		return (FALSE);
	return (TRUE);
}
