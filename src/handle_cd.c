/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:43:14 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/28 16:20:24 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *av)
{
	if (av == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			perror("chdir");
	}
	else
	{
		if (chdir(av) != 0)
			perror("chdir");
	}
}

void	handle_cd_command(t_shell *shell, char **cmd)
{
	if (cmd[1] == NULL)
		cd(NULL);
	else
		cd(cmd[1]);
	get_promt_name(shell);
	free(cmd);
}
