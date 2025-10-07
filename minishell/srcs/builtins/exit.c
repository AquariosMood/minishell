/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryda-si <bryda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:13:49 by bryda-si          #+#    #+#             */
/*   Updated: 2024/12/05 02:55:34 by bryda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_int_limit(char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (ft_strlen(str) > 11)
		return (0);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
		return (0);
	return (1);
}

long	ft_atol(char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

int	ft_str_is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	execute_exit(t_minishell *minishell, char *arg)
{
	long	exit_code;

	if (!ft_str_is_numeric(arg) || !check_int_limit(arg))
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, " : numeric argument required\n", 30);
		free_minishell(minishell);
		exit(2);
	}
	exit_code = ft_atol(arg);
	free_minishell(minishell);
	exit((unsigned char)exit_code);
}

int	ft_exit(t_minishell *minishell, t_command *command)
{
	if (!minishell || !command)
	{
		free_minishell(minishell);
		exit(0);
	}
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
	if (!command->args[1])
	{
		free_minishell(minishell);
		exit(minishell->exit_code);
	}
	if (command->args[2] && ft_str_is_numeric(command->args[1]))
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		minishell->exit_code = 1;
		return (FALSE);
	}
	execute_exit(minishell, command->args[1]);
	return (TRUE);
}
