/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:08:18 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/26 12:59:32 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error(char *s)
{
	static char	*error;

	if (error == NULL && s != NULL)
	{
		error = s;
		return (1);
	}
	else if (error == NULL)
		return (0);
	perror(error);
	error = NULL;
	return (1);
}

int	se_find_type(t_token *token)
{
	t_red_type	red_type;

	if (token->type == TOKEN_PIPE)
		return (error(SE_PIPE));
	red_type = get_red_type(token);
	if (red_type == REDIR_APPEND)
		return (error(SE_APPEND));
        else if (red_type == REDIR_HEREDOC)
		return (error(SE_HEREDOC));
        else if (red_type == REDIR_IN)
		return (error(SE_REDIN));
        else
                return (error(SE_REDOUT));
}

int	se_token(t_token *token)
{
	t_token	*next;

	if (token->type == TOKEN_PIPE)
		return(error(SE_PIPE));
	next = token->next;
	while (next != NULL)
	{
		if (token->type == TOKEN_REDIRECTION && next->type != TOKEN_WORD)
			return (se_find_type(token));
		token = next;
		next = next->next;
	}
	if (token->type != TOKEN_WORD)
		return(se_find_type(token));
	return (0);
}
