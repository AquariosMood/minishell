/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:15:53 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/06 01:13:22 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_argument(t_token **head, t_token **current, char *ptr)
{
	t_token	*new_token;
	char	*tmp;

	tmp = ft_strdup(ptr);
	if (!tmp)
		return ;
	new_token = create_token(TOKEN_ARGUMENT, tmp);
	if (!new_token)
	{
		free(tmp);
		return ;
	}
	add_token(head, current, new_token);
	*ptr = *(ptr + 1);
}
