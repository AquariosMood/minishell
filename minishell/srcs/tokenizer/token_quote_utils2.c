/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-13 21:15:46 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-13 21:15:46 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	convert_exit_status(char *buffer, int exit_status)
{
	size_t	len;
	char	tmp[12];
	int		i;
	int		j;

	i = 0;
	if (exit_status == 0)
	{
		buffer[0] = '0';
		return (1);
	}
	while (exit_status > 0)
	{
		tmp[i++] = (exit_status % 10) + '0';
		exit_status /= 10;
	}
	len = i;
	j = 0;
	while (--i >= 0)
		buffer[j++] = tmp[i];
	return (len);
}

size_t	handle_dollar_in_quotes(char **ptr, char *buffer,
	t_minishell *minishell, char quote)
{
	size_t	pos;

	pos = 0;
	if (*(*ptr + 1) == '?')
	{
		(*ptr)++;
		pos += convert_exit_status(buffer, minishell->exit_code);
		(*ptr)++;
	}
	else if ((*(*ptr + 1) && ft_isalnum(*(*ptr + 1))) || *(*ptr + 1) == '_')
	{
		(*ptr)++;
		pos += convert_in_quote(minishell, buffer, *ptr, quote);
		while (*ptr && **ptr && **ptr != quote && **ptr != ' '
			&& (ft_isalnum(**ptr) || **ptr == '_'))
			(*ptr)++;
	}
	else
	{
		buffer[pos++] = **ptr;
		(*ptr)++;
	}
	return (pos);
}

size_t	handle_token_in_buffer(char **ptr, char *buffer, t_minishell *minishell)
{
	size_t	pos;
	char	quote;

	pos = 0;
	quote = **ptr;
	(*ptr)++;
	while (*ptr && **ptr && **ptr != quote)
	{
		if (quote == '"' && **ptr == '$')
		{
			pos += handle_dollar_in_quotes(ptr, &buffer[pos], minishell, quote);
		}
		else
			buffer[pos++] = *(*ptr)++;
	}
	if (*ptr && **ptr == quote)
		(*ptr)++;
	return (pos);
}

size_t	handle_dollar_in_buffer(char **ptr, char *buffer,
	t_minishell *minishell)
{
	size_t	pos;

	pos = 0;
	if (*(*ptr + 1) == '?')
	{
		(*ptr)++;
		pos += convert_exit_status(buffer, minishell->exit_code);
		(*ptr)++;
	}
	else if ((*(*ptr + 1) && ft_isalnum(*(*ptr + 1))) || *(*ptr + 1) == '_')
	{
		(*ptr)++;
		pos += convert_in_quote(minishell, buffer, *ptr, 0);
		while ((*ptr && **ptr && check_special_char(**ptr)
				&& ft_isalnum(**ptr)) || **ptr == '_')
			(*ptr)++;
	}
	else
	{
		buffer[pos++] = **ptr;
		(*ptr)++;
	}
	return (pos);
}
