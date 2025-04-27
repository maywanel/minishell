/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:50:13 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/27 21:51:59 by moel-mes         ###   ########.fr       */
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
    free(shell->line);
}
