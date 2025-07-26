/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 08:42:47 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/26 11:52:39 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	token_addback(t_token **token, t_token *new_token)
{
	t_token	*saver;

	saver = *token;
	if (*token == NULL)
	{
		*token = new_token;
		return ;
	}
	while ((*token)->next != NULL)
		*token = (*token)->next;
	(*token)->next = new_token;
	*token = saver;
}

t_token	*get_lexer(char *s)
{
	t_token	*token;
	t_token	*node;
	int	start;

	token = NULL;
	start = 0;
	while (1)
	{
		node = split(s, &start);
		if (node == NULL)
			return (token);
		token_addback(&token, node);
	}
	return (token);
}
