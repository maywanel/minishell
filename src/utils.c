/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:35:36 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/06 15:28:04 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_promt_name(t_shell *shell)
{
    char *last_dir;
    char buffer[1024];
    char *tmp;

    tmp = NULL;
    shell->name = NULL;
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        last_dir = ft_strrchr(buffer, '/');
        if (last_dir != NULL)
            last_dir++;
        else
            last_dir = buffer;
        free(shell->name);
        tmp = ft_strjoin("\033[0;36m\e[1m", last_dir);
        last_dir = ft_strjoin(tmp, "\e[m\033[0m ");
        free(tmp);
        shell->name = ft_strdup(last_dir);
        free(last_dir);
    } else {
        perror("getcwd");
    }
}
