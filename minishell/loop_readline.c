/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-25 10:32:40 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-25 10:32:40 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input_quote(char *input)
{
	char	initial_quote;
	char	final_quote;
	int		i;

	initial_quote = '0';
	final_quote = '0';
	i = 0;
	if (!input)
		return (FALSE);
	while (input[i] && (input[i] != '\'' && input[i] != '"'))
		i++;
	if (input[i] == '\0')
		return (TRUE);
	initial_quote = input[i];
	i++;
	while (input[i])
	{
		if (input[i] && (input[i] == '\'' || input[i] == '"'))
			final_quote = input[i];
		i++;
	}
	if (initial_quote == final_quote)
		return (TRUE);
	return (FALSE);
}

static int	process_input(t_minishell *minishell, char *input)
{
	if (!input)
		return (FALSE);
	if (input[0] != '\0')
		add_history(input);
	if (input[0] == '\0')
	{
		free(input);
		minishell->exit_code = 0;
		return (TRUE);
	}
	g_in_command_execution = 1;
	minishell_v1(minishell, input);
	free(input);
	return (TRUE);
}

int	loop_readline(t_minishell *minishell)
{
	char	*input;
	char	*prompt;

	prompt = "minishell-1.0$ ";
	rl_outstream = stderr;
	while (1)
	{
		g_in_command_execution = 0;
		input = readline(prompt);
		if (g_sigint_received)
		{
			minishell->exit_code = 130;
			g_sigint_received = 0;
		}
		if (!process_input(minishell, input))
			break ;
	}
	return (rl_clear_history(), TRUE);
}
