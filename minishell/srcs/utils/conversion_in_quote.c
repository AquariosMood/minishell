/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_in_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:57:24 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/14 13:24:48 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	size_convert_in_quote(char *ptr, char quote)
{
	size_t	i;

	if (!ptr || !*ptr)
		return (0);
	i = 0;
	if (quote == '"')
	{
		while (ptr && ptr[i] != '"' && ptr[i] != ' ')
			i++;
	}
	else
	{
		while (ptr[i] && ptr[i] != ' ' && ptr[i] != '"' && ptr[i] != '\'')
			i++;
	}
	return (i);
}

char	*tmp_content_dollar(char *ptr, char quote)
{
	size_t	i;
	size_t	size;
	char	*tmp;

	if (!ptr || !*ptr)
		return (NULL);
	size = size_convert_in_quote(ptr, quote);
	if (size == 0)
		return (NULL);
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (ptr[i] && (ft_isalnum(ptr[i]) || ptr[i] == '_') && i < size)
	{
		tmp[i] = ptr[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

size_t	convert_in_quote(t_minishell *minishell, char *buffer, char *ptr,
		char quote)
{
	size_t	i;
	char	*tmp;
	char	*uniq_env;

	if (!ptr || !*ptr || !buffer || !minishell->copy_env)
		return (0);
	if (*ptr == '?' && quote == 0)
		return (handle_exit_status(&ptr, buffer, minishell->exit_code));
	tmp = tmp_content_dollar(ptr, quote);
	if (!tmp)
		return (0);
	uniq_env = get_env_uniq(minishell->copy_env, tmp);
	free(tmp);
	if (!uniq_env)
		return (0);
	i = 0;
	while (uniq_env[i])
	{
		buffer[i] = uniq_env[i];
		i++;
	}
	return (i);
}

size_t	size_content_dollar(char **ptr, t_copy_env *env)
{
	size_t	size;
	char	*tmp;
	char	*env_value;

	size = 0;
	if (!*ptr || !**ptr)
		return (0);
	(*ptr)++;
	tmp = tmp_content_dollar(*ptr, 0);
	if (tmp)
	{
		env_value = get_env_uniq(env, tmp);
		if (env_value)
			size += ft_strlen(env_value);
		free(tmp);
		while (*ptr && **ptr && check_special_char(**ptr) && **ptr != ' '
			&& (ft_isalnum(**ptr) || **ptr == '_'))
			(*ptr)++;
	}
	return (size);
}
