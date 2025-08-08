/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:53:44 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/08 08:22:19 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_pipe_command(t_cmd *cmd, t_shell *shell, int *input_fd,
		int pipefd[2])
{
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			pro_collect(NULL);
			exit(EXIT_FAILURE);
		}
	}
	p_handle_child_process(cmd, shell, *input_fd, pipefd);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*input_fd = pipefd[0];
	}
}

static void	check_status(void)
{
	int	status;
	int	sig;

	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
			{
				printf("\n");
				get_exit_code(130);
			}
			else if (sig == SIGQUIT)
			{
				write(2, "Quit (core dumped)\n", 19);
				get_exit_code(131);
			}
			else
				get_exit_code(0);
		}
		else if (WIFEXITED(status))
			get_exit_code(WEXITSTATUS(status));
	}
}

void	handle_pipes(t_shell *shell)
{
	int		pipefd[2];
	int		input_fd;
	t_cmd	*cmd;

	input_fd = STDIN_FILENO;
	cmd = shell->cmd_list;
	preprocess_all_heredocs(shell);
	while (cmd)
	{
		process_pipe_command(cmd, shell, &input_fd, pipefd);
		cmd = cmd->next;
	}
	check_status();
}
