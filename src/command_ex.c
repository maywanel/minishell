/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:44:32 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/06 15:42:18 by moel-mes         ###   ########.fr       */
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
    if (access(shell->path, X_OK) == -1)
    {
        printf("minishell: %s: Permission denied\n", cmd[0]);
        free_array(cmd);
        free(shell->path);
        shell->path = NULL;
        return;
    }
    execute_command(shell, cmd);
}

void handle_script(t_shell *shell, char **cmd)
{
    int arg_count;
    char **script_cmd;
    int i;
    arg_count = 0;
    while (cmd[arg_count])
        arg_count++;
    script_cmd = malloc(sizeof(char *) * (arg_count + 2));
    if (!script_cmd) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    script_cmd[0] = ft_strdup("/bin/bash");
    script_cmd[1] = ft_strdup(shell->path);
    i = 1;
    while (i < arg_count)
    {
        script_cmd[i + 1] = ft_strdup(cmd[i]);
        i++;
    }
    script_cmd[arg_count + 1] = NULL;
    execve("/bin/bash", script_cmd, shell->envp);
    free_array(script_cmd);
    perror("minishell");
    exit(EXIT_FAILURE);
    
}

void execute_command(t_shell *shell, char **cmd)
{
    pid_t pid;
    int len;
    
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        len = ft_strlen(shell->path);
        if (len > 3 && ft_strncmp(shell->path + len - 3, ".sh", 3) == 0)
            handle_script(shell, cmd);
        else if (execve(shell->path, cmd, shell->envp) == -1)
        {
            perror("minishell");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
        perror("fork");
    else
        handle_child_process(shell, pid);
    signal(SIGINT, handle_sigint);
    free_array(cmd);
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