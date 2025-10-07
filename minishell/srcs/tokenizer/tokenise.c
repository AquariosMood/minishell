/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:22:36 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/14 13:23:58 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenise(char *input, t_minishell *minishell)
{
	t_token	*head;
	t_token	*current;
	char	*ptr;

	ptr = input;
	head = NULL;
	current = NULL;
	while (ptr && *ptr == ' ')
		ptr++;
	while (ptr && *ptr && *ptr != '\n')
	{
		if (ptr && *ptr == '|')
			ptr = token_pipe(&head, &current, ptr);
		else if (ptr && *ptr == '>')
			ptr = redirect_output_or_append(&head, &current, ptr);
		else if (ptr && *ptr == '<')
			ptr = redirect_input_or_heredoc(&head, &current, ptr);
		else
			ptr = token_other(&head, &current, ptr, minishell);
	}
	if (!check_token(head, head))
		return (free_tokens(head), NULL);
	return (head);
}
