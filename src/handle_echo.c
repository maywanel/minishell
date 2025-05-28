/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:35:59 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/28 16:19:55 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_echo(t_shell *shell, char **cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!cmd || !cmd[0] || shell == NULL)
		return ;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			newline = 0;
			i++;
		}
		else
			break ;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}
