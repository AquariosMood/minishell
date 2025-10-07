/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 10:14:35 by bryda-si          #+#    #+#             */
/*   Updated: 2025-03-10 10:14:35 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	disable_echoctl(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static size_t	expand_heredoc_length_dollar(t_minishell *minishell,
	char **line_ptr)
{
	size_t	len;

	len = 0;
	if (**line_ptr == '$')
	{
		if (*(*line_ptr + 1) == '?')
		{
			len = size_exit_status(minishell->exit_code);
			*line_ptr += 2;
		}
		else if (*(*line_ptr + 1) && (ft_isalnum(*(*line_ptr + 1))
				|| *(*line_ptr + 1) == '_'))
			len = size_content_dollar(line_ptr, minishell->copy_env);
		else
		{
			len = 1;
			(*line_ptr)++;
		}
	}
	return (len);
}

size_t	expand_heredoc_length(t_minishell *minishell, char *line)
{
	size_t	len;

	len = 0;
	while (line && *line)
	{
		if (*line == '$')
			len += expand_heredoc_length_dollar(minishell, &line);
		else
		{
			len++;
			line++;
		}
	}
	return (len);
}

static size_t	process_dollar_expansion(t_minishell *minishell,
	char **line, char *res)
{
	size_t	pos;

	pos = 0;
	if (*(*line + 1) == '?')
	{
		pos += convert_exit_status(res + pos, minishell->exit_code);
		*line += 2;
	}
	else if (*(*line + 1) && (ft_isalnum(*(*line + 1)) || *(*line + 1) == '_'))
	{
		pos += convert_in_quote(minishell, res + pos, *line + 1, 0);
		(*line)++;
		while (**line && (ft_isalnum(**line) || **line == '_'))
			(*line)++;
	}
	else
	{
		res[pos++] = **line;
		(*line)++;
	}
	return (pos);
}

size_t	fill_expanded_heredoc(t_minishell *minishell, char *line, char *res)
{
	size_t	pos;

	pos = 0;
	while (line && *line)
	{
		if (*line == '$')
			pos += process_dollar_expansion(minishell, &line, res + pos);
		else
			res[pos++] = *line++;
	}
	res[pos] = '\0';
	return (pos);
}
