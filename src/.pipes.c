/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:53:44 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/30 09:09:47 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handel_heredoc(t_cmd *cmd, t_shell *shell, int pipefd[2])
{
    char *line;
    int fd_heredoc = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_heredoc == -1)
        (perror("open heredoc"), exit(EXIT_FAILURE));
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, cmd->delimiter) == 0)
            break;
        write(fd_heredoc, line, ft_strlen(line));
        write(fd_heredoc, "\n", 1);
        free(line);
    }
    free(line);
    close(fd_heredoc);
    dup2(open(".heredoc_tmp", O_RDONLY), STDIN_FILENO);
    unlink(".heredoc_tmp");
}

static void setup_redirection(t_cmd *cmd)
{
    int fd_out;
    int fd_in;
    if (cmd->infile)
    {
        fd_in = open(cmd->infile, O_RDONLY);
        if (fd_in == -1)
            (perror("open infile"), exit(EXIT_FAILURE));
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    if (cmd->outfile)
    {
        if (cmd->append)
            fd_out = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
        else
            fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
            (perror("open outfile"), exit(EXIT_FAILURE));
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}

static void execute_command(t_cmd *cmd, t_shell *shell, int pipefd[2])
{
    if (cmd->next)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        (close(pipefd[0]), close(pipefd[1]));
    }
    if (cmd->heredoc)
        handle_heredoc(cmd, shell, pipefd);
    setup_redirection(cmd);
    char *path = find_path(cmd->argv);
    if (!path)
    {
        fprintf(stderr, "Command not found: %s\n", cmd->argv[0]);
        exit(EXIT_FAILURE);
    }
    execve(path, cmd->argv, shell->envp);
    (perror("execve"), exit(EXIT_FAILURE));
}

static void handle_child_process(t_cmd *cmd, t_shell *shell, int pipefd[2])
{
    pid_t pid = fork();
    if (pid == -1)
        (perror("fork"), exit(EXIT_FAILURE));
    if (pid == 0)
        execute_command(cmd, shell, pipefd);
}

void handle_pipes(t_shell *shell)
{
    int pipefd[2];
    t_cmd *cmd = shell->cmd_list;

    while (cmd)
    {
        if (cmd->next && pipe(pipefd) == -1)
            (perror("pipe"), exit(EXIT_FAILURE));
        handle_child_process(cmd, shell, pipefd);
        if (cmd->next)
        {
            close(pipefd[1]);
            (dup2(pipefd[0], STDIN_FILENO), close(pipefd[0]));
        }
        cmd = cmd->next;
    }
    while (wait(NULL) > 0);
}
