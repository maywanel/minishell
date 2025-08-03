/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 08:42:47 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/01 12:45:05 by hamel-yo         ###   ########.fr       */
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

t_token	*make_token_node(char *s)
{
	t_token	*node;

	if (s == NULL)
		return (NULL);
	node = malloc(sizeof(t_token));
	node->txt = ft_strdup(s);
	node->len = ft_strlen(s);
	node->next = NULL;
	return (node);
}

t_token	*get_lexer(char *s, char squotes, char dquotes)
{
	t_token	*token;
	t_token	*node;
	int		start;

	token = NULL;
	start = 0;
	while (1)
	{
		node = split(s, &start, squotes, dquotes);
		if (node == NULL)
			break ;
		token_addback(&token, node);
	}
	if (token != NULL && se_token(token) == 1)
	{
		detect_error(NULL);
		return (NULL);
	}
	return (token);
}
