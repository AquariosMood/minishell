/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:38:52 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/14 12:51:08 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option_echo(t_command *command)
{
	int	i;
	int	j;
	int	nbr_arg;

	i = 1;
	nbr_arg = 0;
	if (!command || !command->args)
		return (FALSE);
	while (command->args[i] && command->args[i][0] == '-'
		&& command->args[i][1] == 'n')
	{
		j = 1;
		while (command->args[i][j])
		{
			if (command->args[i][j] != 'n')
				return (nbr_arg);
			j++;
		}
		i++;
		nbr_arg++;
	}
	return (nbr_arg);
}

int	malloc_echo(t_command *command, int len_option)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!command || !command->args)
		return (0);
	while (command->args[i])
	{
		if (i < len_option)
			j = 1;
		else
			j += ft_strlen(command->args[i]);
		if (command->args[i + 1] && i >= len_option)
			j++;
		i++;
	}
	return (j);
}

void	init_str(t_command *command, char *str, int *k, int len_option)
{
	int	i;
	int	j;

	i = 1;
	(void)len_option;
	if (!command || !command->args)
		return ;
	while (len_option-- > 0)
		i++;
	while (command->args[i])
	{
		j = 0;
		while (command->args[i][j])
		{
			str[*k] = command->args[i][j];
			j++;
			*k += 1;
		}
		if (command->args[i + 1])
		{
			str[*k] = ' ';
			*k += 1;
		}
		i++;
	}
}

void	push_args_to_str(t_command *command, char *str, int len_option)
{
	int	k;

	k = 0;
	init_str(command, str, &k, len_option);
	if (len_option == 0)
	{
		str[k] = '\n';
		k++;
	}
	str[k] = '\0';
}

int	ft_echo(t_minishell *minishell, t_command *command, int fd_out)
{
	char	*str;
	int		len_option;

	(void)minishell;
	if (!command || !command->args)
		return (FALSE);
	len_option = check_option_echo(command);
	str = malloc((malloc_echo(command, len_option) + 2)
			* sizeof(char));
	if (!str)
		return (FALSE);
	push_args_to_str(command, str, len_option);
	if (write(fd_out, str, ft_strlen(str)) == -1)
	{
		free(str);
		free_minishell(minishell);
		return (FALSE);
	}
	free(str);
	minishell->exit_code = 0;
	return (TRUE);
}
