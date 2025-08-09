/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:25:00 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/09 08:33:44 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_int_to_str(char *str, int num, int *i)
{
	int	tmp;
	int	power;
	int	digit;

	if (num == 0)
	{
		str[(*i)++] = '0';
		return ;
	}
	tmp = num;
	power = 1;
	while (tmp >= 10)
	{
		tmp /= 10;
		power *= 10;
	}
	tmp = num;
	while (power > 0)
	{
		digit = tmp / power;
		str[(*i)++] = digit + '0';
		tmp %= power;
		power /= 10;
	}
}

static char	*create_heredoc_filename(int cmd_index, int heredoc_index)
{
	char	*filename;
	int		i;

	i = 0;
	filename = pro_malloc(50);
	if (!filename)
		return (NULL);
	filename[i++] = '.';
	filename[i++] = 'h';
	filename[i++] = 'e';
	filename[i++] = 'r';
	filename[i++] = 'e';
	filename[i++] = 'd';
	filename[i++] = 'o';
	filename[i++] = 'c';
	filename[i++] = '_';
	filename[i++] = 't';
	filename[i++] = 'm';
	filename[i++] = 'p';
	filename[i++] = '_';
	append_int_to_str(filename, cmd_index, &i);
	filename[i++] = '_';
	append_int_to_str(filename, heredoc_index, &i);
	filename[i] = '\0';
	return (filename);
}

static void	process_single_heredoc(char **env, t_red *redir, char *filename)
{
	char	*line;
	int		fd_heredoc;

	fd_heredoc = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_heredoc == -1)
	{
		perror("open heredoc");
		pro_collect(NULL);
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strncmp(line, redir->target,
					ft_strlen(redir->target)) == 0
				&& ft_strlen(line) == ft_strlen(redir->target)))
			break ;
		line = get_heredoc_line(env, redir, line);
		write(fd_heredoc, line, ft_strlen(line));
		write(fd_heredoc, "\n", 1);
		free(line);
	}
	free(line);
	close(fd_heredoc);
}

static void	process_cmd_heredocs(char **env, t_cmd *cmd, int cmd_index)
{
	t_red	*redir;
	int		heredoc_index;
	char	*filename;

	redir = cmd->redirection;
	heredoc_index = 0;
	while (redir)
	{
		if (redir->red_type == REDIR_HEREDOC)
		{
			filename = create_heredoc_filename(cmd_index, heredoc_index);
			if (filename)
			{
				process_single_heredoc(env, redir, filename);
				redir->target = filename;
				heredoc_index++;
			}
		}
		redir = redir->next;
	}
}

void	preprocess_all_heredocs(t_shell *shell)
{
	t_cmd	*cmd;
	int		cmd_index;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		(signal(SIGINT, heredoc_sig), signal(SIGQUIT, SIG_DFL));
		cmd = shell->cmd_list;
		cmd_index = 0;
		while (cmd)
		{
			process_cmd_heredocs(shell->envp, cmd, cmd_index);
			cmd = cmd->next;
			cmd_index++;
		}
		exit(0);
	}
	else if (pid > 0)
		(signal(SIGINT, SIG_IGN), check_status(pid),
			signal(SIGINT, handle_sigint));
	else
		(perror("fork"), exit(EXIT_FAILURE));
}
