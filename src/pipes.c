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

static char *create_heredoc_filename(int cmd_index, int heredoc_index)
{
    char *filename = malloc(50);
    if (!filename)
        return NULL;
    sprintf(filename, ".heredoc_tmp_%d_%d", cmd_index, heredoc_index);
    return filename;
}

static void process_single_heredoc(t_red *redir, char *filename)
{
    char *line;
    int fd_heredoc = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_heredoc == -1)
        (perror("open heredoc"), exit(EXIT_FAILURE));
    while (1)
    {
        line = readline("> ");
        if (!line || (ft_strncmp(line, redir->target, ft_strlen(redir->target)) == 0 && 
            ft_strlen(line) == ft_strlen(redir->target)))
            break;
        write(fd_heredoc, line, ft_strlen(line));
        write(fd_heredoc, "\n", 1);
        free(line);
    }
    free(line);
    close(fd_heredoc);
}

static void preprocess_all_heredocs(t_shell *shell)
{
    t_cmd *cmd = shell->cmd_list;
    int cmd_index;
    int heredoc_index;

    cmd_index = 0;
    while (cmd)
    {
        t_red *redir = cmd->redirection;
        heredoc_index = 0;
        
        while (redir)
        {
            if (redir->red_type == REDIR_HEREDOC)
            {
                char *filename = create_heredoc_filename(cmd_index, heredoc_index);
                if (filename)
                {
                    process_single_heredoc(redir, filename);
                    free(redir->target);
                    redir->target = filename;
                    heredoc_index++;
                }
            }
            redir = redir->next;
        }
        cmd = cmd->next;
        cmd_index++;
    }
}

void setup_redirection(t_cmd *cmd)
{
    t_red *redir;
    int fd;

    if (!cmd || !cmd->redirection)
        return;
    
    redir = cmd->redirection;
    while (redir)
    {
        if (redir->red_type == REDIR_IN)
        {
            fd = open(redir->target, O_RDONLY);
            if (fd == -1)
                (perror("open infile"), exit(EXIT_FAILURE));
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (redir->red_type == REDIR_OUT)
        {
            fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                (perror("open outfile"), exit(EXIT_FAILURE));
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->red_type == REDIR_APPEND)
        {
            fd = open(redir->target, O_WRONLY | O_APPEND | O_CREAT, 0644);
            if (fd == -1)
                (perror("open outfile"), exit(EXIT_FAILURE));
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->red_type == REDIR_HEREDOC)
        {
            fd = open(redir->target, O_RDONLY);
            if (fd == -1)
                (perror("open heredoc"), exit(EXIT_FAILURE));
            dup2(fd, STDIN_FILENO);
            close(fd);
            unlink(redir->target);
        }
        redir = redir->next;
    }
}

char **tokens_to_argv(t_token *token)
{
    int count = 0;
    t_token *temp = token;
    char **argv;
    int i;
    
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return NULL;
    i = 0;
    temp = token;
    while (temp)
    {
        argv[i] = malloc(temp->len + 1);
        if (!argv[i])
            return NULL;
        ft_strlcpy(argv[i], temp->txt, temp->len + 1);
        temp = temp->next;
        i++;
    }
    argv[i] = NULL;
    return argv;
}

static void p_execute_command(t_cmd *cmd, t_shell *shell, int input_fd, int pipefd[2])
{
    char **argv;
    char *path;
    
    if (!cmd->token)
        exit(EXIT_FAILURE);
        
    argv = tokens_to_argv(cmd->token);
    if (!argv)
        exit(EXIT_FAILURE);
    
    if (ft_strncmp(argv[0], "exit", 4) == 0 && ft_strlen(argv[0]) == 4)
    {
        int exit_code = 0;
        if (argv[1] != NULL)
        {
            if (ft_isdigit(argv[1][0]))
                exit_code = ft_exit_code(argv[1]);
            else
                exit_code = 255;
        }
        exit(exit_code);
    }
    
    if (is_builtin(shell, argv))
        exit(EXIT_SUCCESS);
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
    if (input_fd != STDIN_FILENO)
    {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    
    if (cmd->next)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
    }
    
    setup_redirection(cmd);   
    path = find_path(shell, argv);
    if (!path)
    {
        fprintf(stderr, "Command not found: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    execve(path, argv, shell->envp);
    (perror("execve"), exit(EXIT_FAILURE));
}

void p_handle_child_process(t_cmd *cmd, t_shell *shell, int input_fd, int pipefd[2])
{
    pid_t pid = fork();
    if (pid == -1)
        (perror("fork"), exit(EXIT_FAILURE));
    if (pid == 0)
        p_execute_command(cmd, shell, input_fd, pipefd);
}

void handle_pipes(t_shell *shell)
{
    int pipefd[2];
    int input_fd = STDIN_FILENO;
    t_cmd *cmd = shell->cmd_list;

    preprocess_all_heredocs(shell);
    while (cmd)
    {
        if (cmd->next)
        {
            if (pipe(pipefd) == -1)
                (perror("pipe"), exit(EXIT_FAILURE));
        }
        
        p_handle_child_process(cmd, shell, input_fd, pipefd);
        
        if (input_fd != STDIN_FILENO)
            close(input_fd);
            
        if (cmd->next)
        {
            close(pipefd[1]);
            input_fd = pipefd[0];
        }
        
        cmd = cmd->next;
    }
    while (wait(NULL) > 0);
}

