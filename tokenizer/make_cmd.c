/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:10:08 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/08 16:31:09 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*split_tokenw(t_token **lexer)
{
	t_token	*result;
	t_token	*next;

	result = *lexer;
	next = (*lexer)->next;
	while (next != NULL)
	{
		if (next->type != TOKEN_WORD)
			break ;
		*lexer = next;
		next = next->next;
	}
	if (next != NULL)
		(*lexer)->next = NULL;
	*lexer = next;
	return (result);
}

void	token_add_back(t_token **token, t_token **lexer)
{
	t_token	*saver;

	saver = *token;
	if (*token == NULL)
	{
		*token = split_tokenw(lexer);
		return ;
	}
	while ((*token)->next != NULL)
		*token = (*token)->next;
	(*token)->next = split_tokenw(lexer);
	*token = saver;
}

t_red	*make_red(t_token **lexer, t_shell *shell)
{
	t_red	*redirect;

	redirect = pro_malloc(sizeof(t_red));
	if (!redirect)
		return (NULL);
	redirect->red_type = get_red_type(*lexer);
	redirect->token = (*lexer)->next;
	*lexer = (*lexer)->next;
	*lexer = (*lexer)->next;
	if (redirect->red_type != REDIR_HEREDOC)
		redirect->token = ex_redirection(redirect->token, shell->envp);
	if (!redirect->token)
		return ((void *)-1);
	redirect->target = redirect->token->txt;
	redirect->next = NULL;
	return (redirect);
}

t_cmd	*make_cmd(t_token *lexer, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = pro_malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirection = NULL;
	cmd->token = NULL;
	cmd->next = NULL;
	while (lexer != NULL)
	{
		if (lexer->type == TOKEN_WORD)
			token_add_back(&(cmd->token), &lexer);
		else if (lexer->type == TOKEN_REDIRECTION)
			red_add_back(&(cmd->redirection), &lexer, shell);
		else if (lexer->type == TOKEN_PIPE)
		{
			lexer = lexer->next;
			cmd->next = make_cmd(lexer, shell);
			break ;
		}
		else
			lexer = lexer->next;
	}
	return (cmd);
}

t_cmd	*get_the_parser(char *s, t_shell *shell)
{
	t_token	*lexer;
	t_cmd	*cmd;

	lexer = get_lexer(s, '\'', '\"');
	if (lexer == NULL)
		return (NULL);
	cmd = make_cmd(lexer, shell);
	if (cmd && cmd->redirection == (void *)-1)
		return (NULL);
	return (cmd);
}
