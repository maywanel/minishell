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

void	handle_exit(t_shell *shell, char **cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd[1] != NULL)
	{
		if (ft_isdigit(cmd[1][0]))
			exit_code = ft_exit_code(cmd[1]);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			exit_code = 255;
		}
	}
	
	*shell->last_exit_code = exit_code;
	printf("exit\n");
	shell->running = false;
}
