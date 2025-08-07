/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:50:13 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/07 14:00:59 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_shell *shell, char **cmd)
{
	int	ex;

	ex = 0;
	if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
		ex = handle_cd_command(shell, cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0 && ft_strlen(cmd[0]) == 4)
		ex = handle_exit(shell, cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && ft_strlen(cmd[0]) == 3)
		ex = handle_pwd();
	else if (ft_strncmp(cmd[0], "export", 6) == 0 && ft_strlen(cmd[0]) == 6)
		ex = handle_export(shell, cmd);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0 && ft_strlen(cmd[0]) == 5)
		ex = handle_unset(cmd, shell);
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && ft_strlen(cmd[0]) == 3)
		ex = handle_env(shell);
	else if (ft_strncmp(cmd[0], "echo", 4) == 0 && ft_strlen(cmd[0]) == 4)
		ex = handle_echo(shell, cmd);
	return (ex);
}

bool	is_builtin_command(char *cmd)
{
	if (!cmd)
		return (false);
	if ((ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4)
		|| (ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2)
		|| (ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6)
		|| (ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5))
		return (true);
	return (false);
}

bool	is_cbuiltin_command(char *cmd)
{
	if (!cmd)
		return (false);
	if ((ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3)
		|| (ft_strncmp(cmd, "env", 3) == 0 && ft_strlen(cmd) == 3)
		|| (ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4))
		return (true);
	return (false);
}

void	execute_builtin_in_child(t_shell *shell, char **cmd)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		setup_redirection(shell->cmd_list);
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		exit(is_builtin(shell, cmd));
	}
	else if (pid < 0)
	{
		perror("fork");
		get_exit_code(1);
	}
	else
		handle_child_process(pid);
	signal(SIGINT, handle_sigint);
}
