/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:34:09 by moel-mes          #+#    #+#             */
/*   Updated: 2025/06/16 00:37:16 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

char	*find_path(t_shell *shell, char **cmd)
{
	char	*path;
	int		i;
	char	*tmp;
	char	**paths;

	i = 0;
	if (!cmd || !cmd[0])
		return (NULL);
	if (access(cmd[0], F_OK) == 0)
		return (cmd[0]);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		return (ft_strdup(cmd[0]));
	path = ft_getenv(shell, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ":");
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (free_array(paths), path);
		free(path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

void	prompt(t_shell *shell)
{
	char	**cmd;
	char	*tmp;

	cmd = NULL;
	tmp = ft_strjoin("\033[0;32m\e[1m➜\e[m  ", shell->name);
	shell->line = readline(tmp);
	free(tmp);
	if (!shell->line)
		return (handle_exit(shell));
	if (ft_strlen(shell->line) > 0)
	{
		add_history(shell->line);
		cmd = ft_split(shell->line, " \t\n\r\f\v");
		handle_command(shell, cmd);
	}
	free(shell->line);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	int		exit_code;

	(void)ac;
	(void)av;
	exit_code = 0;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	shell->envp = envp;
	shell->envp = get_envp(shell);
	shell->line = NULL;
	shell->cmd_list = NULL;
	shell->last_exit_code = 0;
	shell->running = true;
	get_promt_name(shell);
	while (shell->running)
		prompt(shell);
	exit_code = shell->last_exit_code;
	free(shell->name);
	free_array(shell->envp);
	free(shell);
	exit(exit_code);
}
