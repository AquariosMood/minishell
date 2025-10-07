/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:08:26 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/14 13:23:36 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*push_token_in_buffer(char *ptr, char *buffer, t_minishell *minishell)
{
	size_t	pos;

	pos = 0;
	while (ptr && *ptr && check_special_char(*ptr))
	{
		if (ptr && (*ptr == '"' || *ptr == '\''))
			pos += handle_token_in_buffer(&ptr, &buffer[pos], minishell);
		else if (*ptr == '$')
			pos += handle_dollar_in_buffer(&ptr, &buffer[pos], minishell);
		else
			buffer[pos++] = *ptr++;
	}
	buffer[pos] = '\0';
	return (ptr);
}

static size_t	handle_token_char_size(char **tmp_ptr, t_minishell *minishell,
	char *start_ptr)
{
	size_t	char_size;
	char	initial_quote;

	char_size = 0;
	if (**tmp_ptr == '"' || **tmp_ptr == '\'')
	{
		initial_quote = **tmp_ptr;
		start_ptr = *tmp_ptr;
		(*tmp_ptr)++;
		char_size = handle_quoted_size(*tmp_ptr, initial_quote, minishell);
		while (*tmp_ptr && **tmp_ptr && **tmp_ptr != initial_quote)
			(*tmp_ptr)++;
		if (*tmp_ptr && **tmp_ptr == initial_quote)
			(*tmp_ptr)++;
		if (char_size == 0 && *tmp_ptr > start_ptr)
			char_size = 1;
	}
	else if (**tmp_ptr == '$')
		char_size = handle_dollar_unquoted(tmp_ptr, minishell);
	else
	{
		char_size = 1;
		(*tmp_ptr)++;
	}
	return (char_size);
}

static size_t	calculate_token_size(char *ptr, t_minishell *minishell)
{
	size_t	size;
	char	*tmp_ptr;
	char	*start_ptr;

	if (!ptr || !*ptr)
		return (0);
	size = 0;
	tmp_ptr = ptr;
	start_ptr = NULL;
	while (tmp_ptr && *tmp_ptr && *tmp_ptr != ' ')
		size += handle_token_char_size(&tmp_ptr, minishell, start_ptr);
	return (size);
}

static char	*handle_empty_token(char *ptr, t_minishell *minishell)
{
	if (*ptr && (*ptr == '"' || *ptr == '\''))
		ptr++;
	while (ptr && *ptr && *ptr != ' ' && *ptr != '"' && *ptr != '\'')
		ptr++;
	while (ptr && *ptr == ' ')
		ptr++;
	minishell->exit_code = 0;
	return (ptr);
}

char	*token_quote_or_no_quote(t_token **head, t_token **current, char *ptr,
	t_minishell *minishell)
{
	t_token	*token;
	size_t	size;
	char	*buffer;

	size = calculate_token_size(ptr, minishell);
	if (size == 0)
		return (handle_empty_token(ptr, minishell));
	buffer = malloc((size + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ptr = push_token_in_buffer(ptr, buffer, minishell);
	token = create_token(minishell->type, buffer);
	if (!token)
		return (free(buffer), NULL);
	add_token(head, current, token);
	while (ptr && *ptr == ' ')
		ptr++;
	return (ptr);
}
