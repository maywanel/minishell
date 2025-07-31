/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 08:29:51 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/31 09:31:39 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ef_token(t_token *token)
{
	t_token	*n_token;
	t_token	*tmp;

	n_token = NULL;
	while (token)
	{
		if (token->txt)
		{
			tmp = get_lexer(token->txt, -1, -1);
			if (!tmp)
				break ;
			token_addback(&n_token, tmp);
		}
		token = token->next;
	}
	return (n_token);
}
