/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:44:08 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/28 16:21:22 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_exit_code(char *str)
{
	long	code;

	code = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		code = code * 10 + (*str - '0');
		str++;
	}
	return (code);
}

void	handle_exit(t_shell *shell)
{
	char	**exit_code;

	if (!shell->line)
	{
		printf("exit\n");
		shell->running = false;
		return ;
	}
	exit_code = ft_split(shell->line, " ");
	if (exit_code[1] == NULL)
		shell->last_exit_code = 0;
	else if (ft_isdigit(exit_code[1][0]))
		shell->last_exit_code = ft_exit_code(exit_code[1]);
	else
	{
		printf("minishell: exit: %s: numeric argument required\n",
			exit_code[1]);
		free_array(exit_code);
	}
	free_array(exit_code);
	printf("exit\n");
	shell->running = false;
}
