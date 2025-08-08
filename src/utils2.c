/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:10:30 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/07 14:10:30 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char **cmd, char *error_msg, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd && cmd[0])
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_msg, 2);
	get_exit_code(exit_code);
}

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
		exit(130);
	}
}
