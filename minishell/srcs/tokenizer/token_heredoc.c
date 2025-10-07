/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:25 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:14:28 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_heredoc(t_token **head, t_token **current, char *ptr)
{
	t_token	*new_token;
	char	*tmp;

	tmp = ft_strdup("<<");
	if (!tmp)
		return (NULL);
	new_token = create_token(TOKEN_HEREDOC, tmp);
	if (!new_token)
		return (NULL);
	add_token(head, current, new_token);
	ptr = ptr + 2;
	while (ptr && *ptr == ' ')
		ptr++;
	return (ptr);
}

char	*token_here_string(t_token **head, t_token **current, char *ptr)
{
	t_token	*new_token;
	char	*tmp;

	tmp = ft_strdup("<<<");
	if (!tmp)
		return (NULL);
	new_token = create_token(TOKEN_HERE_STRING, tmp);
	if (!new_token)
		return (NULL);
	add_token(head, current, new_token);
	ptr = ptr + 3;
	while (ptr && *ptr == ' ')
		ptr++;
	return (ptr);
}
