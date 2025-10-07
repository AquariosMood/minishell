/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirect_in_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-08 18:47:09 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-08 18:47:09 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*create_redirect_in_command(char *name_file,
	enum e_token_type type, int index_redirect)
{
	t_redirect	*new_redirect;

	if (!name_file)
		return (NULL);
	new_redirect = malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (NULL);
	new_redirect->file = ft_strdup(name_file);
	if (!new_redirect->file)
	{
		free(new_redirect);
		return (NULL);
	}
	new_redirect->type = type;
	new_redirect->index = index_redirect;
	new_redirect->next = NULL;
	return (new_redirect);
}
