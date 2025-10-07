/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-25 10:16:06 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-25 10:16:06 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_pipeline(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			return (TRUE);
		tokens = tokens->next;
	}
	return (FALSE);
}

static int	has_redirections(t_token *tokens)
{
	t_token	*token;

	if (!tokens)
		return (FALSE);
	token = tokens;
	while (token)
	{
		if (token->type == TOKEN_REDIRECT_INPUT
			|| token->type == TOKEN_REDIRECT_OUTPUT
			|| token->type == TOKEN_REDIRECT_APPEND
			|| token->type == TOKEN_HEREDOC)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

static int	process_and_execute(t_minishell *minishell)
{
	if (!init_heredoc(minishell->commands, minishell))
	{
		if (g_sigint_received)
		{
			g_sigint_received = 0;
			minishell->exit_code = 130;
		}
		else
			minishell->exit_code = 1;
		free_tokens(minishell->tokens);
		free_command(minishell->commands);
		return (FALSE);
	}
	if (has_pipeline(minishell->tokens))
		minishell->exit_code = execute_pipeline_with_redirects(minishell);
	else if (has_redirections(minishell->tokens))
		minishell->exit_code = execute_single_command_with_redirects(minishell,
				minishell->commands);
	else
		execute_command(minishell, STDOUT_FILENO);
	free_tokens(minishell->tokens);
	free_command(minishell->commands);
	return (TRUE);
}

int	minishell_v1(t_minishell *minishell, char *input)
{
	if (!minishell || !input)
		return (FALSE);
	if (!check_input_quote(input))
	{
		write(2, "minishell: quote error\n", 24);
		minishell->exit_code = 2;
		return (FALSE);
	}
	minishell->tokens = tokenise(input, minishell);
	if (!minishell->tokens)
	{
		minishell->exit_code = 2;
		return (FALSE);
	}
	minishell->commands = convert_token_to_command(minishell->tokens);
	if (!minishell->commands)
	{
		minishell->exit_code = 0;
		return (free_tokens(minishell->tokens), FALSE);
	}
	normalize_commands(minishell->commands);
	return (process_and_execute(minishell));
}
