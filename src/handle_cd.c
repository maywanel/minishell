/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:43:14 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/07 14:43:40 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *av)
{
	if (av == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("chdir");
			return ;
		}
	}
	else
	{
		if (chdir(av) != 0)
		{
			perror("chdir");
			return ;
		}
	}
}

int	handle_cd_command(t_shell *shell, char **cmd)
{
	int	arg_count;
	int	ex;

	ex = 0;
	arg_count = 0;
	while (cmd[arg_count])
		arg_count++;
	if (arg_count > 2)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (cmd[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("minishell: cd");
			ex = 1;
		}
	}
	else if (chdir(cmd[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ex = 1;
	}
	return (get_promt_name(shell), ex);
}
