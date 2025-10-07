/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect_output.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:17:08 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:18:48 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_redirect_output(t_token **head, t_token **current, char *ptr)
{
	t_token	*new_token;
	char	*tmp;

	tmp = ft_strdup(">");
	if (!tmp)
		return (NULL);
	new_token = create_token(TOKEN_REDIRECT_OUTPUT, tmp);
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

char	*redirect_output_or_append(t_token **head, t_token **current, char *ptr)
{
	if (ptr && *(ptr + 1) == '>')
		return (token_redirect_append(head, current, ptr));
	else
		return (token_redirect_output(head, current, ptr));
}
