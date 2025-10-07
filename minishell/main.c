/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:53:55 by bryda-si          #+#    #+#             */
/*   Updated: 2025/01/16 14:17:56 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint_received = 0;
int	g_in_command_execution = 0;

int	main(void)
{
	t_minishell	minishell;

	if (!init_all_struct_minishell(&minishell))
		return (FALSE);
	check_isatty(&minishell);
	free_copy_env(minishell.copy_env);
	return (minishell.exit_code);
}
