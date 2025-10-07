/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:21:43 by bryda-si          #+#    #+#             */
/*   Updated: 2024/11/12 14:21:50 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sep(char s, char c)
{
	return (s == c || s == '\0');
}

static size_t	count_size_word(const char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (sep(s[i], c) == 0 && s[i])
		i++;
	return (i);
}

static int	count_word(char const *s, char c)
{
	int	i;
	int	count_word;

	i = 0;
	count_word = 0;
	while (s[i] != '\0')
	{
		if (sep(s[i], c) == 0 && sep(s[i + 1], c) == 1)
			count_word++;
		i++;
	}
	return (count_word);
}

static char	*words(char const *s, char c)
{
	char	*word;
	int		i;

	if (!s)
		return (NULL);
	word = malloc((count_size_word(s, c) + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (sep(*s, c) == 0 && *s)
	{
		word[i] = *s++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**string;
	int		i;
	int		word_jump;

	if (!s)
		return (NULL);
	string = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!string)
		return (NULL);
	i = 0;
	word_jump = 0;
	while (*s)
	{
		if (sep(*s, c) == 0 && word_jump == 0)
		{
			string[i] = words(s, c);
			i++;
			word_jump++;
		}
		else if (sep(*s, c) == 1)
			word_jump = 0;
		s++;
	}
	string[i] = NULL;
	return (string);
}
