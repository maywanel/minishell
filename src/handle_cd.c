/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:43:14 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/06 10:15:49 by moel-mes         ###   ########.fr       */
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

void	handle_cd_command(t_shell *shell, char **cmd)
{
	if (cmd[1] == NULL)
	{
		cd(NULL);
		if (chdir(getenv("HOME")) != 0)
			get_exit_code(1);
		else
			get_exit_code(0);
	}
	else
	{
		if (chdir(cmd[1]) != 0)
			get_exit_code(1);
		else
			get_exit_code(0);
	}
	get_promt_name(shell);
}
