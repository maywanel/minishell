/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:34:09 by moel-mes          #+#    #+#             */
/*   Updated: 2025/07/27 10:25:50 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_command(t_shell *shell)
{
	if (ft_strlen(shell->line) == 0)
		return ;
	add_history(shell->line);
	shell->cmd_list = get_the_parser(shell->line);
	if (!shell->cmd_list)
		return ;
	if (shell->cmd_list->next)
		handle_pipes(shell);
	else
	{
		shell->cmd_list->argv = tokens_to_argv(shell->cmd_list->token);
		if (shell->cmd_list->argv)
			handle_command(shell, shell->cmd_list->argv);
		else
			free(shell->cmd_list);
	}
}

void	prompt(t_shell *shell)
{
	char	*tmp;
	char	*exit_cmd[2];

	exit_cmd[0] = "exit";
	exit_cmd[1] = NULL;
	tmp = ft_strjoin("\033[0;32m\e[1m➜\e[m  ", shell->name);
	shell->line = readline(tmp);
	free(tmp);
	if (!shell->line)
		return (handle_exit(shell, exit_cmd));
	process_command(shell);
	free(shell->line);
}

static void	init_shell(t_shell *shell)
{
	shell->envp = get_envp(shell);
	shell->line = NULL;
	shell->cmd_list = NULL;
	*shell->last_exit_code = 0;
	shell->running = true;
	get_promt_name(shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	int		exit_code;

	(void)ac;
	(void)av;
	shell = malloc(sizeof(t_shell));
	shell->last_exit_code = malloc(sizeof(long));
	if (!shell || !shell->last_exit_code)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	shell->envp = envp;
	init_shell(shell);
	while (shell->running)
		prompt(shell);
	exit_code = *shell->last_exit_code;
	free(shell->name);
	free(shell->last_exit_code);
	free_array(shell->envp);
	free(shell);
	return (exit_code);
}
