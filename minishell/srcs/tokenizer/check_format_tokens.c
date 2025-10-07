/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:33:21 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:10:44 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_format_tokens_pipe(t_token *head, t_token *tokens)
{
	if (head && head->type == TOKEN_PIPE)
	{
		write(STDERR_FILENO,
			"minishell: syntax error near unexpected token `|'\n", 50);
		return (FALSE);
	}
	if (tokens && tokens->type != TOKEN_COMMAND
		&& tokens->type != TOKEN_ARGUMENT
		&& tokens->type != TOKEN_FILE)
	{
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			if ((tokens && tokens->next && (tokens->next->type == TOKEN_COMMAND
						|| tokens->next->type == TOKEN_ARGUMENT
						|| tokens->next->type == TOKEN_REDIRECT_INPUT
						|| tokens->next->type == TOKEN_REDIRECT_OUTPUT
						|| tokens->next->type == TOKEN_REDIRECT_APPEND
						|| tokens->next->type == TOKEN_HEREDOC)))
				return (TRUE);
			else
				return (FALSE);
		}
	}
	return (TRUE);
}

int	check_formats_tokens_output_append(t_token *head, t_token *tokens)
{
	(void)head;
	if ((tokens && (tokens->type == TOKEN_REDIRECT_OUTPUT
				|| tokens->type == TOKEN_REDIRECT_APPEND)))
	{
		if ((tokens && (!tokens->next || tokens->next->type != TOKEN_FILE)))
		{
			write(STDERR_FILENO,
				"minishell: syntax error near unexpected token `", 48);
			if (!tokens->next)
				write(STDERR_FILENO, "newline", 7);
			else
				write(STDERR_FILENO,
					tokens->next->value, ft_strlen(tokens->next->value));
			write(STDERR_FILENO, "'\n", 2);
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	check_formats_tokens_input(t_token *head, t_token *tokens)
{
	(void)head;
	if (tokens && tokens->type == TOKEN_REDIRECT_INPUT)
	{
		if (tokens && (!tokens->next || tokens->next->type != TOKEN_FILE))
		{
			write(STDERR_FILENO,
				"minishell: syntax error near unexpected token `", 48);
			if (!tokens->next)
				write(STDERR_FILENO, "newline", 7);
			else
				write(STDERR_FILENO,
					tokens->next->value, ft_strlen(tokens->next->value));
			write(STDERR_FILENO, "'\n", 2);
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	check_formats_tokens_heredoc(t_token *head, t_token *tokens)
{
	(void)head;
	if (tokens && tokens->type == TOKEN_HEREDOC)
	{
		if (tokens && (!tokens->next || tokens->next->type != TOKEN_DELIMITER))
		{
			write(STDERR_FILENO,
				"minishell: syntax error near unexpected token `", 48);
			if (!tokens->next)
				write(STDERR_FILENO, "newline", 7);
			else
				write(STDERR_FILENO,
					tokens->next->value, ft_strlen(tokens->next->value));
			write(STDERR_FILENO, "'\n", 2);
			return (FALSE);
		}
	}
	return (TRUE);
}

int	check_formats_tokens_input_heredoc(t_token *head, t_token *tokens)
{
	if (!check_formats_tokens_input(head, tokens))
		return (FALSE);
	if (!check_formats_tokens_heredoc(head, tokens))
		return (FALSE);
	return (TRUE);
}
