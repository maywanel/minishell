/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:34:58 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/08 10:01:43 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_command(char **argv)
{
	int		code;
	long	temp_code;

	code = 0;
	if (argv[1])
	{
		if (argv[2] != NULL)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		if (!is_valid_number(argv[1]))
			return (ft_print_error(&argv[1],
					"minishell: exit: %s: numeric argument required\n", 2), 2);
		temp_code = ft_exit_code(argv[1]);
		if (temp_code == LONG_MAX)
		{
			ft_print_error(&argv[1],
				"minishell: exit: %s: numeric argument required\n", 2);
			return (255);
		}
		code = (unsigned char)temp_code;
	}
	return (code);
}

static void	execute_builtin_or_exit(t_shell *shell, char **argv)
{
	int	code;

	if (ft_strncmp(argv[0], "exit", 4) == 0 && ft_strlen(argv[0]) == 4)
	{
		code = handle_exit_command(argv);
		exit(code);
	}
	if (is_cbuiltin_command(argv[0]) || is_builtin_command(argv[0]))
		exit(is_builtin(shell, argv));
}

static void	setup_pipes_and_signals(t_cmd *cmd, int input_fd, int pipefd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (cmd->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

static void	p_execute_command(t_cmd *cmd, t_shell *shell, int input_fd,
		int pipefd[2])
{
	char	**argv;
	char	*path;

	if (!cmd->token)
		exit(EXIT_FAILURE);
	shell->cmd_list->token = last_token(shell->cmd_list->token, shell->envp);
	argv = tokens_to_argv(cmd->token);
	if (!argv)
		exit(EXIT_FAILURE);
	(setup_pipes_and_signals(cmd, input_fd, pipefd), setup_redirection(cmd));
	execute_builtin_or_exit(shell, argv);
	path = find_path(shell, argv);
	if (!path)
	{
		ft_print_error(&argv[0], "minishell: %s: command not found\n", 127);
		exit(127);
	}
	if (access(path, X_OK) == -1)
	{
		ft_print_error(&argv[0],
			"minishell: %s: Permission denied\n", 126);
		exit(126);
	}
	execve(path, argv, shell->envp);
	(perror("execve"), exit(EXIT_FAILURE));
}

void	p_handle_child_process(t_cmd *cmd, t_shell *shell, int input_fd,
		int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		p_execute_command(cmd, shell, input_fd, pipefd);
}
