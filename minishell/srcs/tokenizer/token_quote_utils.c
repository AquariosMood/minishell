/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-12 20:48:33 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-12 20:48:33 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	handle_quoted_content_size(char **ptr, char quote, t_copy_env *env)
{
	size_t	size;

	size = 0;
	while (*ptr && **ptr && **ptr != quote)
	{
		if (quote == '"' && **ptr == '$' && *(*ptr + 1))
			size += size_content_dollar(ptr, env);
		else
		{
			size++;
			(*ptr)++;
		}
	}
	if (*ptr && **ptr == quote)
		(*ptr)++;
	return (size);
}

size_t	handle_dollar_quoted(char **ptr, t_minishell *minishell)
{
	size_t	size;

	size = 0;
	if (*(*ptr + 1) == '?')
	{
		*ptr += 2;
		size = size_exit_status(minishell->exit_code);
	}
	else if (*(*ptr + 1) && (ft_isalnum(*(*ptr + 1))
			|| *(*ptr + 1) == '_'))
		size = size_content_dollar(ptr, minishell->copy_env);
	else
	{
		size = 1;
		(*ptr)++;
	}
	return (size);
}

size_t	handle_quoted_size(char *ptr, char initial_quote,
	t_minishell *minishell)
{
	size_t	size;

	size = 0;
	while (ptr && *ptr && *ptr != initial_quote)
	{
		if (initial_quote == '"' && *ptr == '$')
			size += handle_dollar_quoted(&ptr, minishell);
		else
		{
			size++;
			ptr++;
		}
	}
	return (size);
}

size_t	handle_dollar_unquoted(char **ptr, t_minishell *minishell)
{
	size_t	size;

	size = 0;
	if (*(*ptr + 1) == '?')
	{
		(*ptr)++;
		size = size_exit_status(minishell->exit_code);
	}
	else if (*(*ptr + 1) && (ft_isalnum(*(*ptr + 1))
			|| *(*ptr + 1) == '_'))
		size = size_content_dollar(ptr, minishell->copy_env);
	else
	{
		size = 1;
		(*ptr)++;
	}
	return (size);
}

size_t	handle_unquoted_size(char *ptr, t_minishell *minishell)
{
	size_t	size;

	size = 0;
	while (ptr && *ptr && check_special_char(*ptr))
	{
		if (*ptr == '$')
			size += handle_dollar_unquoted(&ptr, minishell);
		else
		{
			size++;
			ptr++;
		}
	}
	return (size);
}
