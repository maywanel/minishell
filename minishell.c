/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:34:09 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/26 20:53:26 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void cd(char *av)
{
    if (av == NULL)
    {
        if (chdir(getenv("HOME")) != 0)
            perror("chdir");
    }
    else
    {
        if (chdir(av) != 0)
            perror("chdir");
    }
}

char *find_path(char **cmd)
{
    char *path;
    char *full_path;

    if (access(cmd[0], F_OK) == 0)
        return (cmd[0]);
    path = getenv("PATH");
    if (!path)
        return (NULL);
    char **paths = ft_split(path, ':');
    for (int i = 0; paths[i]; i++)
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd[0]);
        if (access(full_path, F_OK) == 0)
        {
            free(paths);
            return (full_path);
        }
        free(full_path);
    }
    free(paths);
    return (NULL);
}

void handle_cd_command(t_shell *shell, char **cmd)
{
    char buffer[1024];
    char *last_dir;

    if (cmd[1] == NULL)
        cd(NULL);
    else
        cd(cmd[1]);
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        last_dir = strrchr(buffer, '/');
        if (last_dir != NULL)
            last_dir++;
        else
            last_dir = buffer;
        free(shell->name);
        shell->name = ft_strdup(last_dir);
    } else {
        perror("getcwd");
    }
    free(cmd);
    free(shell->line);
}

void prompt(t_shell *shell)
{
    char **cmd;
    char *path;

    shell->line = readline(ft_strjoin(shell->name, "> "));
    if (!shell->line)
    {
        printf("\n");
        shell->running = false;
        return;
    }
    if (ft_strlen(shell->line) > 0)
    {
        add_history(shell->line);
        cmd = ft_split(shell->line, ' ');
        if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
        {
            handle_cd_command(shell, cmd);
            return;
        }
        path = find_path(cmd);
        if (fork() == 0)
        {
            if (execve(path, cmd, shell->envp) == -1)
            {
                perror("minishell");
                exit(EXIT_FAILURE);
            }
        }
        else
            wait(NULL);
    }
    free(shell->line);
}

int	main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;

    t_shell *shell = malloc(sizeof(t_shell));
    if (!shell)
        return (1);
    shell->envp = envp;
    shell->line = NULL;
    shell->cmd_list = NULL;
    shell->last_exit_code = 0;
    shell->running = true;
    shell->name = ft_strdup("minishell");
    while (shell->running)
        prompt(shell);
    free(shell->line);
    free(shell);
    return (0);
}
