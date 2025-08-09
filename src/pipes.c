/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:53:44 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/09 17:48:22 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	process_pipe_command(t_cmd *cmd, t_shell *shell, int *input_fd,
		int pipefd[2])
{
	pid_t	pid;

	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			pro_collect(NULL);
			exit(EXIT_FAILURE);
		}
	}
	pid = p_handle_child_process(cmd, shell, *input_fd, pipefd);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*input_fd = pipefd[0];
	}
	return (pid);
}

void	check_status(pid_t pid)
{
	int	status;
	int	sig;

	while (waitpid(pid, &status, 0) != -1)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
			{
				write(1, "\n", 1);
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

void	wait_for_all_processes(pid_t *pids, t_cmd *cmd)
{
	int		i;
	pid_t	last_pid;
	int		cmd_count;

	cmd_count = 0;
	while (cmd)
	{
		cmd_count++;
		cmd = cmd->next;
	}
	if (cmd_count == 0)
		return ;
	last_pid = pids[cmd_count - 1];
	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] == last_pid)
			check_status(pids[i]);
		else
			waitpid(pids[i], NULL, 0);
		i++;
	}
}

void	handle_pipes(t_shell *shell)
{
	int		pipefd[2];
	int		input_fd;
	t_cmd	*cmd;
	pid_t	*pids;
	int		i;

	input_fd = STDIN_FILENO;
	cmd = shell->cmd_list;
	i = 0;
	while (cmd && ++i)
		cmd = cmd->next;
	pids = pro_malloc(sizeof(pid_t) * i);
	cmd = shell->cmd_list;
	preprocess_all_heredocs(shell);
	i = 0;
	while (cmd)
	{
		cmd->token = last_token(cmd->token, shell->envp);
		pids[i] = process_pipe_command(cmd, shell, &input_fd, pipefd);
		cmd = cmd->next;
		i++;
	}
	wait_for_all_processes(pids, shell->cmd_list);
}
