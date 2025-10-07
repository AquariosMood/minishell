/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:17:31 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:12:34 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tokens_repeat_type(t_token *tokens, enum e_token_type type,
		char *value_type)
{
	(void)value_type;
	if (tokens && tokens->type != type)
		return (TRUE);
	if (tokens && tokens->next && tokens->type == tokens->next->type)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected token `",
			48);
		write(STDERR_FILENO, tokens->value, ft_strlen(tokens->value));
		write(STDERR_FILENO, "'\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

int	check_tokens_repeat_all_type(t_token *tokens)
{
	if (!check_tokens_repeat_type(tokens, TOKEN_PIPE, "|"))
		return (FALSE);
	if (!check_tokens_repeat_type(tokens, TOKEN_REDIRECT_OUTPUT, ">"))
		return (FALSE);
	if (!check_tokens_repeat_type(tokens, TOKEN_REDIRECT_APPEND, ">>"))
		return (FALSE);
	if (!check_tokens_repeat_type(tokens, TOKEN_REDIRECT_INPUT, "<"))
		return (FALSE);
	if (!check_tokens_repeat_type(tokens, TOKEN_HEREDOC, "<<"))
		return (FALSE);
	return (TRUE);
}

int	check_token(t_token *head, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (!check_tokens_repeat_all_type(tmp)
			|| !check_format_tokens_pipe(head, tmp)
			|| !check_formats_tokens_output_append(head, tmp)
			|| !check_formats_tokens_input_heredoc(head, tmp))
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}
