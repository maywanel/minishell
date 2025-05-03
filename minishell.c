/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:34:09 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/29 10:40:43 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	// rl_redisplay();
}

char *find_path(char **cmd)
{
    char *path;
    char *full_path;
    char *tmp;

    if (access(cmd[0], F_OK) == 0)
        return (cmd[0]);
    path = getenv("PATH");
    if (!path)
        return (NULL);
    char **paths = ft_split(path, ":");
    for (int i = 0; paths[i]; i++)
    {
        tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, cmd[0]);
        free(tmp);
        if (access(full_path, X_OK) == 0)
        {
            free_array(paths);
            return (full_path);
        }
        free(full_path);
    }
    free_array(paths);
    return (NULL);
}

void prompt(t_shell *shell)
{
    char **cmd;
    char *tmp;

    tmp = ft_strjoin(shell->name, "> ");
    shell->line = readline(tmp);
    free(tmp);
    if (!shell->line)
        return handle_exit(shell);
    if (ft_strlen(shell->line) > 0)
    {
        add_history(shell->line);
        cmd = ft_split(shell->line, " \t\n\r\f\v");
        handle_command(shell, cmd);
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
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN); // Ignore "CTL+\"
    shell->envp = envp;
    shell->line = NULL;
    shell->cmd_list = NULL;
    shell->last_exit_code = 0;
    shell->running = true;
    shell->name = ft_strdup("minishell");
    while (shell->running)
        prompt(shell);
    free(shell->name);
    free(shell);
    return (0);
}
