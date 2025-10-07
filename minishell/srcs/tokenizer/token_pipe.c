/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:07:36 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:14:44 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_pipe(t_token **head, t_token **current, char *ptr)
{
	t_token	*new_token;
	char	*tmp;

	tmp = ft_strdup("|");
	if (!tmp)
		return (NULL);
	new_token = create_token(TOKEN_PIPE, tmp);
	if (!new_token)
	{
		free(tmp);
		return (NULL);
	}
	add_token(head, current, new_token);
	ptr++;
	while (ptr && *ptr == ' ')
		ptr++;
	return (ptr);
}
