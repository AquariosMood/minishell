/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_isatty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-24 10:08:11 by bryda-si          #+#    #+#             */
/*   Updated: 2025-02-24 10:08:11 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_char_to_line(char *line, size_t len, char c)
{
	char	*tmp;

	tmp = malloc(len + 2);
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	ft_memcpy(tmp, line, len);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	free(line);
	return (tmp);
}

static ssize_t	read_loop(int fd, char **line, size_t *len)
{
	char	buffer[1];
	ssize_t	rd_bytes;

	while (1)
	{
		rd_bytes = read(fd, buffer, 1);
		if (rd_bytes < 0)
			return (rd_bytes);
		if (rd_bytes == 0)
		{
			if (*len > 0)
				continue ;
			else
				break ;
		}
		if (buffer[0] == '\n')
			break ;
		*line = append_char_to_line(*line, *len, buffer[0]);
		if (!(*line))
			return (-1);
		(*len)++;
	}
	return (rd_bytes);
}

char	*read_line_from_fd(int fd)
{
	size_t	len;
	char	*line;
	ssize_t	rd_bytes;

	len = 0;
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	rd_bytes = read_loop(fd, &line, &len);
	if (rd_bytes == 0 && len == 0)
		return (free(line), NULL);
	return (line);
}

int	check_isatty(t_minishell *minishell)
{
	char	*line;

	if (!minishell)
		return (FALSE);
	if (isatty(STDIN_FILENO) == 0)
	{
		while (1)
		{
			line = read_line_from_fd(STDIN_FILENO);
			if (!line)
				break ;
			if (line[0] != '\0')
				minishell_v1(minishell, line);
			free(line);
		}
		return (1);
	}
	else
	{
		loop_readline(minishell);
		return (1);
	}
	return (0);
}
