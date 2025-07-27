/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:08:18 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/27 10:30:44 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	detect_error(char *s)
{
	static char	*error;

	if (error == NULL && s != NULL)
	{
		error = s;
		ft_putstr_fd(error, 2);
		return (1);
	}
	if (error == NULL && s == NULL)
		return (0);
	if (error != NULL)
		error = NULL;
	return (1);
}

int	se_find_type(t_token *token)
{
	t_red_type	red_type;

	if (token->type == TOKEN_PIPE)
		return (detect_error(SE_PIPE));
	red_type = get_red_type(token);
	if (red_type == REDIR_APPEND)
		return (detect_error(SE_APPEND));
	else if (red_type == REDIR_HEREDOC)
		return (detect_error(SE_HEREDOC));
	else if (red_type == REDIR_IN)
		return (detect_error(SE_REDIN));
	else
		return (detect_error(SE_REDOUT));
}

int	se_token(t_token *token)
{
	t_token	*next;

	if (detect_error(NULL) == 1)
		return (1);
	if (token->type == TOKEN_PIPE)
		return (detect_error(SE_PIPE));
	next = token->next;
	while (next != NULL)
	{
		if (token->type == TOKEN_REDIRECTION && next->type != TOKEN_WORD)
			return (se_find_type(next));
		token = next;
		next = next->next;
	}
	if (token->type != TOKEN_WORD)
		return (detect_error(SE_NL));
	return (0);
}
