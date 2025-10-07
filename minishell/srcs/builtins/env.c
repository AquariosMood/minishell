/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:23:31 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/07 04:33:45 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_uniq(t_copy_env *copy_env, char *name)
{
	t_copy_env	*tmp;

	if (!copy_env)
		return (NULL);
	tmp = copy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	find_size_malloc_env(void)
{
	int	i;
	int	size;

	if (!environ)
		return (FALSE);
	i = 0;
	size = 0;
	while (environ[i])
	{
		size += (ft_strlen(environ[i]) + 1);
		i++;
	}
	return (size);
}

void	push_env_to_str(char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j])
		{
			str[k] = environ[i][j];
			j++;
			k++;
		}
		str[k] = '\n';
		k++;
		i++;
	}
	str[k] = '\0';
}

// int	ft_env(t_minishell *minishell, int fd_out)
// {
// 	char	*str;

// 	(void)minishell;
// 	str = malloc(sizeof(char) * (find_size_malloc_env()));
// 	if (!str)
// 		return (FALSE);
// 	push_env_to_str(str);
// 	if (write(fd_out, str, ft_strlen(str)) == -1)
// 	{
// 		free(str);
// 		return (FALSE);
// 	}
// 	free(str);
// 	return (TRUE);
// }

int	ft_env(t_minishell *minishell, t_command *command, int fd_out)
{
	t_copy_env	*tmp;

	(void)command;
	if (!minishell || !minishell->copy_env)
		return (FALSE);
	tmp = minishell->copy_env;
	while (tmp)
	{
		if (tmp->is_exported)
		{
			write(fd_out, tmp->name, ft_strlen(tmp->name));
			write(fd_out, "=", 1);
			write(fd_out, tmp->value, ft_strlen(tmp->value));
			write(fd_out, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
