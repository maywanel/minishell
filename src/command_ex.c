/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:44:32 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/28 10:46:46 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_command(t_shell *shell, char **cmd)
{
    if (is_builtin(shell, cmd))
        return;
    shell->path = find_path(cmd);
    if (!shell->path)
    {
        printf("minishell: %s: command not found\n", cmd[0]);
        free_array(cmd);
        return;
    }
    execute_command(shell, cmd);
}

void execute_command(t_shell *shell, char **cmd)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (execve(shell->path, cmd, shell->envp) == -1)
        {
            perror("minishell");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
        perror("fork");
    else
        handle_child_process(shell, pid);
    free_array(cmd);
    free(shell->path);
}

void handle_child_process(t_shell *shell, pid_t pid)
{
    int status;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);
        shell->last_exit_code = (sig == SIGINT) ? 130 : (sig == SIGQUIT) ? 131 : 0;
    }
    else if (WIFEXITED(status))
        shell->last_exit_code = WEXITSTATUS(status);
}