/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:44:32 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/08 10:00:03 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_command_path(t_shell *shell, char **cmd)
{
	struct stat	file_stat;

	shell->path = find_path(shell, cmd);
	if (!shell->path)
	{
		ft_print_error(cmd, "command not found\n", 127);
		return (0);
	}
	if (stat(shell->path, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
	{
		ft_print_error(cmd, "Is a directory\n", 126);
		return (0);
	}
	if (access(shell->path, X_OK) == -1)
	{
		if (access(shell->path, F_OK) == 0)
			ft_print_error(cmd, "Permission denied\n", 126);
		else
			ft_print_error(cmd, "No such file or directory\n", 127);
		return (0);
	}
	return (1);
}

void	handle_command(t_shell *shell, char **cmd)
{
	if (is_cbuiltin_command(cmd[0]))
	{
		execute_builtin_in_child(shell, cmd);
		return ;
	}
	if (is_builtin_command(cmd[0]))
	{
		get_exit_code(is_builtin(shell, cmd));
		return ;
	}
	if (validate_command_path(shell, cmd))
		execute_command(shell, cmd);
}

void	handle_script(t_shell *shell, char **cmd)
{
	int		arg_count;
	char	**script_cmd;
	int		i;

	arg_count = 0;
	while (cmd[arg_count])
		arg_count++;
	script_cmd = pro_malloc(sizeof(char *) * (arg_count + 2));
	if (!script_cmd)
	{
		perror("pro_malloc");
		exit(EXIT_FAILURE);
	}
	script_cmd[0] = pro_strdup("/bin/bash");
	script_cmd[1] = pro_strdup(shell->path);
	i = 1;
	while (i < arg_count)
	{
		script_cmd[i + 1] = pro_strdup(cmd[i]);
		i++;
	}
	script_cmd[arg_count + 1] = NULL;
	execve("/bin/bash", script_cmd, shell->envp);
	pro_collect(NULL);
	(perror("minishell"), exit(EXIT_FAILURE));
}

void	execute_command(t_shell *shell, char **cmd)
{
	pid_t	pid;
	int		len;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		setup_redirection(shell->cmd_list);
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		len = ft_strlen(shell->path);
		if (len > 3 && ft_strncmp(shell->path + len - 3, ".sh", 3) == 0)
			handle_script(shell, cmd);
		else if (execve(shell->path, cmd, shell->envp) == -1)
			(perror("minishell"), exit(EXIT_FAILURE));
	}
	else if (pid < 0)
	{
		perror("fork");
		get_exit_code(1);
	}
	else
		handle_child_process(pid);
	shell->path = NULL;
	signal(SIGINT, handle_sigint);
}

void	handle_child_process(pid_t pid)
{
	int		status;
	int		sig;

	waitpid(pid, &status, 0);
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
