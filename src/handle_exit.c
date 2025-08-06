/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:44:08 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/06 10:24:50 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long	ft_exit_code(char *str)
{
	long	code;
	int		sign;
	int		i;

	code = 0;
	sign = 1;
	i = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (code > (LONG_MAX - (str[i] - '0')) / 10)
			return (LONG_MAX);
		code = code * 10 + (str[i] - '0');
		i++;
	}
	return (code * sign);
}

static int	process_exit_arguments(char **cmd)
{
	long	temp_code;

	if (cmd[1] == NULL)
		return (0);
	if (cmd[2] != NULL)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		get_exit_code(1);
		return (-1);
	}
	if (!is_valid_number(cmd[1]))
	{
		fprintf(stderr,
			"minishell: exit: %s: numeric argument required\n", cmd[1]);
		return (2);
	}
	temp_code = ft_exit_code(cmd[1]);
	if (temp_code == LONG_MAX)
	{
		fprintf(stderr,
			"minishell: exit: %s: numeric argument required\n", cmd[1]);
		return (255);
	}
	return ((unsigned char)temp_code);
}

void	handle_exit(t_shell *shell, char **cmd)
{
	int	exit_code;

	printf("exit\n");
	exit_code = process_exit_arguments(cmd);
	if (exit_code == -1)
		return ;
	get_exit_code(exit_code);
	shell->running = false;
}
