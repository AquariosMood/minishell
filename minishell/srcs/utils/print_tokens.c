/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:29:45 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:06:49 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	char	*type[10];

	type[TOKEN_ARGUMENT] = "TOKEN_ARGUMENT";
	type[TOKEN_COMMAND] = "TOKEN_COMMAND";
	type[TOKEN_HEREDOC] = "TOKEN_HEREDOC";
	type[TOKEN_PIPE] = "TOKEN_PIPE";
	type[TOKEN_REDIRECT_APPEND] = "TOKEN_REDIRECT_APPEND";
	type[TOKEN_REDIRECT_INPUT] = "TOKEN_REDIRECT_INPUT";
	type[TOKEN_REDIRECT_OUTPUT] = "TOKEN_REDIRECT_OUTPUT";
	type[TOKEN_FILE] = "TOKEN_FILE";
	type[TOKEN_DELIMITER] = "TOKEN_DELIMITER";
	while (tokens)
	{
		printf("type: %s, value: %s\n", type[tokens->type], tokens->value);
		tokens = tokens->next;
	}
}
