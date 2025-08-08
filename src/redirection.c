/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:20:00 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/08 11:41:31 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input_redirection(t_red *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd == -1)
	{
		perror("open infile");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_output_redirection(t_red *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_append_redirection(t_red *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_heredoc_redirection(t_red *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd == -1)
	{
		perror("open heredoc");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(redir->target);
}

void	setup_redirection(t_cmd *cmd)
{
	t_red	*redir;

	if (!cmd || !cmd->redirection)
		return ;
	redir = cmd->redirection;
	while (redir)
	{
		if (redir->red_type == REDIR_IN)
			handle_input_redirection(redir);
		else if (redir->red_type == REDIR_OUT)
			handle_output_redirection(redir);
		else if (redir->red_type == REDIR_APPEND)
			handle_append_redirection(redir);
		else if (redir->red_type == REDIR_HEREDOC)
			handle_heredoc_redirection(redir);
		redir = redir->next;
	}
}
