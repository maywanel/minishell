/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:35:59 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/06 10:16:01 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_echo_flags(char **cmd, int *newline)
{
	int	i;
	int	j;

	i = 1;
	*newline = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 2;
		while (cmd[i][j] && cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			break ;
		*newline = 0;
		i++;
	}
	return (i);
}

void	handle_echo(t_shell *shell, char **cmd)
{
	int	i;
	int	newline;

	if (!cmd || !cmd[0] || shell == NULL)
		return ;
	i = process_echo_flags(cmd, &newline);
	while (cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
	get_exit_code(0);
}
