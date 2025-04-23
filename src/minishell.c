/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:34:09 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/23 17:54:37 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*my_path(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char *find_path(t_shell *shell, char **cmd)
{
    char *path;
    char *full_path;
    struct stat buffer;

    if (access(cmd[0], F_OK) == 0)
        return (cmd[0]);
    path = my_path("PATH", shell->envp);
    if (!path)
        return (NULL);
    char **paths = ft_split(path, ':');
    for (int i = 0; paths[i]; i++)
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd[0]);
        if (stat(full_path, &buffer) == 0)
        {
            free(paths);
            return (full_path);
        }
        free(full_path);
    }
    free(paths);
    return (NULL);
}

void prompt(t_shell *shell)
{
    char **cmd;
    char *path;

    shell->line = readline("minishell> ");
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
        path = find_path(shell, cmd);
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

    while (shell->running)
        prompt(shell);
    free(shell);
    return (0);
}
