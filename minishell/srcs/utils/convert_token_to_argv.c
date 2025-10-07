/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_to_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:35:22 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/16 13:42:16 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_size_argv(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	if (!tokens)
		return (FALSE);
	tmp = tokens;
	i = 0;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_ARGUMENT || tmp->type == TOKEN_COMMAND)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**convert_token_argument_to_argv(t_token *tokens)
{
	char	**argv;
	int		size;
	int		i;

	size = malloc_size_argv(tokens);
	if (size == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (is_valid_token(tokens->type))
		{
			argv[i] = ft_strdup(tokens->value);
			if (!argv[i])
				return (free_argv(argv), NULL);
			i++;
		}
		tokens = tokens->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	handle_token(t_token **tmp, t_command **head,
	t_command **current)
{
	static unsigned int	index_command;

	if ((*tmp)->type == TOKEN_PIPE)
	{
		*tmp = (*tmp)->next;
		return (TRUE);
	}
	if ((*tmp)->type == TOKEN_COMMAND)
	{
		if (!handle_command_tok(tmp, head, current, index_command++))
			return (FALSE);
		return (TRUE);
	}
	else if (is_redirection((*tmp)->type))
	{
		if (!handle_command_tok(tmp, head, current, index_command++))
			return (FALSE);
		return (TRUE);
	}
	*tmp = (*tmp)->next;
	return (TRUE);
}

t_command	*process_token_list(t_token *tokens)
{
	t_command	*current;
	t_command	*head;
	t_token		*tmp;

	current = NULL;
	head = NULL;
	tmp = tokens;
	while (tmp)
	{
		if (!handle_token(&tmp, &head, &current))
			return (NULL);
	}
	return (head);
}

t_command	*convert_token_to_command(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (process_token_list(tokens));
}
