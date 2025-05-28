/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:50:13 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/28 15:44:35 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_shell *shell, char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
		handle_cd_command(shell, cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0 && ft_strlen(cmd[0]) == 4)
		(handle_exit(shell), free_array(cmd));
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && ft_strlen(cmd[0]) == 3)
		(handle_pwd(shell), free_array(cmd));
	else if (ft_strncmp(cmd[0], "export", 6) == 0 && ft_strlen(cmd[0]) == 6)
		(handle_export(shell, cmd), free_array(cmd));
	else if (ft_strncmp(cmd[0], "unset", 5) == 0 && ft_strlen(cmd[0]) == 5)
		(handle_unset(cmd, shell), free_array(cmd));
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && ft_strlen(cmd[0]) == 3)
		(handle_env(shell), free_array(cmd));
	else if (ft_strncmp(cmd[0], "echo", 4) == 0 && ft_strlen(cmd[0]) == 4)
		(handle_echo(shell, cmd), free_array(cmd));
	else
		return (false);
	return (true);
}

void	handle_pwd(t_shell *shell)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
	{
		perror("getcwd");
		shell->last_exit_code = 1;
	}
}

void	handle_env(t_shell *shell)
{
	char	**env;

	if (!shell || !shell->envp)
	{
		printf("minishell: env: no environment variables set\n");
		return ;
	}
	env = shell->envp;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
