/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:50:13 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/30 09:17:59 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long

void handle_exit(t_shell *shell)
{
    char **exit_code;
    int code;

    exit_code = ft_split(shell->line, " ");
    if (exit_code[1] == NULL)
        code = 0;
    else if (ft_isdigit(exit_code[1][0]))
        code = ft_exit_code(exit_code[1]);
    else
    {
        printf("minishell: exit: %s: numeric argument required\n", exit_code[1]);
        free_array(exit_code);
    }
    printf("exit\n");
    shell->running = false;
}

bool is_builtin(t_shell *shell, char **cmd)
{
    if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
    {
        handle_cd_command(shell, cmd);
        return true;
    }
    if (ft_strncmp(cmd[0], "exit", 4) == 0 && ft_strlen(cmd[0]) == 4)
    {
        handle_exit(shell);
        free_array(cmd);
        return true;
    }
    return false;
}

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

void handle_cd_command(t_shell *shell, char **cmd)
{
    char buffer[1024];
    char *last_dir;

    if (cmd[1] == NULL)
        cd(NULL);
    else
        cd(cmd[1]);
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        last_dir = ft_strrchr(buffer, '/');
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
}
