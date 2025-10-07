/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect_append.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:45 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:17:27 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_redirect_append(t_token **head, t_token **current, char *ptr)
{
	t_token	*new_token;
	char	*tmp;

	tmp = ft_strdup(">>");
	if (!tmp)
		return (NULL);
	new_token = create_token(TOKEN_REDIRECT_APPEND, tmp);
	if (!new_token)
	{
		free(tmp);
		return (NULL);
	}
	add_token(head, current, new_token);
	ptr = ptr + 2;
	while (ptr && *ptr == ' ')
		ptr++;
	return (ptr);
}
