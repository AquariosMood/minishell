/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_to_command_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-14 00:04:28 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-14 00:04:28 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_token(enum e_token_type type)
{
	return (type == TOKEN_ARGUMENT || type == TOKEN_COMMAND);
}

int	is_redirection(enum e_token_type type)
{
	return (type == TOKEN_REDIRECT_INPUT
		|| type == TOKEN_REDIRECT_OUTPUT
		|| type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_HEREDOC
		|| type == TOKEN_PIPE);
}

t_command	*handle_command_tok(t_token **tmp, t_command **head,
	t_command **current, int index_command)
{
	static unsigned int	index_redirect;
	t_command			*new_command;
	char				**argv;

	argv = convert_token_argument_to_argv(*tmp);
	new_command = create_command((*tmp)->value, argv, index_command);
	if (!new_command)
		return (free_argv(argv), NULL);
	add_command(head, current, new_command);
	while (*tmp && ((*tmp)->type == TOKEN_COMMAND
			|| (*tmp)->type == TOKEN_ARGUMENT))
		*tmp = (*tmp)->next;
	while (*tmp)
	{
		if ((*tmp)->type == TOKEN_PIPE || (*tmp)->type == TOKEN_COMMAND)
			break ;
		else if (is_redirection((*tmp)->type))
		{
			if (!handle_redirect_tok(tmp, new_command, index_redirect++))
				return (NULL);
		}
		else
			*tmp = (*tmp)->next;
	}
	return (new_command);
}

t_redirect	*handle_redirect_tok(t_token **tmp,
	t_command *current, int index_redirect)
{
	t_redirect	*new_redirect;
	t_redirect	*last_redirect;

	if (!tmp || !*tmp || !(*tmp)->next)
		return (NULL);
	new_redirect = create_redirect_in_command((*tmp)->next->value,
			(*tmp)->type, index_redirect);
	if (!new_redirect || !current)
		return (NULL);
	if (!current->redirect)
		current->redirect = new_redirect;
	else
	{
		last_redirect = current->redirect;
		while (last_redirect->next)
			last_redirect = last_redirect->next;
		last_redirect->next = new_redirect;
	}
	*tmp = (*tmp)->next->next;
	return (new_redirect);
}
