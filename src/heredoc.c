/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:25:00 by moel-mes          #+#    #+#             */
/*   Updated: 2025/07/27 13:20:21 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc_filename(int cmd_index, int heredoc_index)
{
	char	*filename;

	filename = malloc(50);
	if (!filename)
		return (NULL);
	sprintf(filename, ".heredoc_tmp_%d_%d", cmd_index, heredoc_index);
	return (filename);
}

static void	process_single_heredoc(t_red *redir, char *filename)
{
	char	*line;
	int		fd_heredoc;

	fd_heredoc = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_heredoc == -1)
	{
		perror("open heredoc");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strncmp(line, redir->target,
					ft_strlen(redir->target)) == 0
				&& ft_strlen(line) == ft_strlen(redir->target)))
			break ;
		write(fd_heredoc, line, ft_strlen(line));
		write(fd_heredoc, "\n", 1);
		free(line);
	}
	free(line);
	close(fd_heredoc);
}

static void	process_cmd_heredocs(t_cmd *cmd, int cmd_index)
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
				process_single_heredoc(redir, filename);
				free(redir->target);
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

	cmd = shell->cmd_list;
	cmd_index = 0;
	while (cmd)
	{
		process_cmd_heredocs(cmd, cmd_index);
		cmd = cmd->next;
		cmd_index++;
	}
}
