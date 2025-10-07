/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-12 19:57:47 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-12 19:57:47 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_other(t_token **head, t_token **current, char *ptr,
	t_minishell *minishell)
{
	if (current && (*current) && ((*current)->type == TOKEN_HEREDOC))
	{
		minishell->type = TOKEN_DELIMITER;
		return (token_quote_or_no_quote(head, current, ptr, minishell));
	}
	if (current && (*current) && ((*current)->type != TOKEN_PIPE
			&& (*current)->type != TOKEN_COMMAND
			&& (*current)->type != TOKEN_ARGUMENT
			&& (*current)->type != TOKEN_FILE
			&& (*current)->type != TOKEN_DELIMITER))
	{
		minishell->type = TOKEN_FILE;
		return (token_quote_or_no_quote(head, current, ptr, minishell));
	}
	if ((current && ((*current) == NULL || (*current)->type == TOKEN_PIPE)))
	{
		minishell->type = TOKEN_COMMAND;
		return (token_quote_or_no_quote(head, current, ptr, minishell));
	}
	else
	{
		minishell->type = TOKEN_ARGUMENT;
		return (token_quote_or_no_quote(head, current, ptr, minishell));
	}
}
