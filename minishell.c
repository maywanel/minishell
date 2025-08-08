/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:34:09 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/08 10:19:40 by hamel-yo         ###   ########.fr       */
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
		preprocess_all_heredocs(shell);
		shell->cmd_list->token = last_token(shell->cmd_list->token,
				shell->envp);
		shell->cmd_list->argv = tokens_to_argv(shell->cmd_list->token);
		if (shell->cmd_list->argv)
			handle_command(shell, shell->cmd_list->argv);
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
	{
		handle_exit(shell, exit_cmd);
		return ;
	}
	process_command(shell);
	free(shell->line);
}

static void	init_shell(t_shell *shell)
{
	shell->envp = get_envp(shell);
	shell->line = NULL;
	shell->cmd_list = NULL;
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
	if (!shell)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	shell->envp = envp;
	init_shell(shell);
	while (shell->running)
		prompt(shell);
	exit_code = get_exit_code(-1);
	pro_collect(NULL);
	free(shell);
	return (exit_code);
}
