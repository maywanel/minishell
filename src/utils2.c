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

void	append_int_to_str(char *str, int num, int *i)
{
	int	tmp;
	int	power;
	int	digit;

	if (num == 0)
	{
		str[(*i)++] = '0';
		return ;
	}
	tmp = num;
	power = 1;
	while (tmp >= 10)
	{
		tmp /= 10;
		power *= 10;
	}
	tmp = num;
	while (power > 0)
	{
		digit = tmp / power;
		str[(*i)++] = digit + '0';
		tmp %= power;
		power /= 10;
	}
}

char	*create_heredoc_filename(int cmd_index, int heredoc_index)
{
	char	*filename;
	int		i;

	i = 0;
	filename = pro_malloc(50);
	if (!filename)
		return (NULL);
	filename[i++] = '.';
	filename[i++] = 'h';
	filename[i++] = 'e';
	filename[i++] = 'r';
	filename[i++] = 'e';
	filename[i++] = 'd';
	filename[i++] = 'o';
	filename[i++] = 'c';
	filename[i++] = '_';
	filename[i++] = 't';
	filename[i++] = 'm';
	filename[i++] = 'p';
	filename[i++] = '_';
	append_int_to_str(filename, cmd_index, &i);
	filename[i++] = '_';
	append_int_to_str(filename, heredoc_index, &i);
	filename[i] = '\0';
	return (filename);
}
