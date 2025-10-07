/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:45:04 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/07 01:06:40 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_received = 1;
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			exit(EXIT_FAILURE);
		if (!g_in_command_execution)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

int	init_signal(void)
{
	if (signal(SIGINT, handle_signal) == SIG_ERR)
		return (FALSE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (FALSE);
	return (TRUE);
}

void	enable_echoctl(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
