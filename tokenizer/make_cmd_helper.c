/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:58:45 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/08 12:21:26 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_type	get_token_type(char *s)
{
	if (*s == '>' || *s == '<')
		return (TOKEN_REDIRECTION);
	else if (*s == '|')
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

t_red_type	get_red_type(t_token *token)
{
	if (*(token->txt) == '>' && token->len == 2)
		return (REDIR_APPEND);
	else if (*(token->txt) == '<' && token->len == 2)
		return (REDIR_HEREDOC);
	else if (*(token->txt) == '<')
		return (REDIR_IN);
	else
		return (REDIR_OUT);
}

void	red_add_back(t_red **red, t_token **lexer, t_shell *shell)
{
	t_red	*saver;
	t_red	*tmp;

	saver = *red;
	if (*red == (void *)-1)
		return ;
	if (*red == NULL)
	{
		*red = make_red(lexer, shell);
		return ;
	}
	while ((*red)->next != NULL)
		*red = (*red)->next;
	tmp = make_red(lexer, shell);
	if (tmp->target == NULL)
	{
		red = NULL;
		return ;
	}
	(*red)->next = tmp;
	*red = saver;
}
