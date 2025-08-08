/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:26:43 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/08 10:33:08 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	wild_card_helper(t_token *token, int *i, int *j)
{
	while (token->txt[*i] == '*' && *i < token->len)
		*i = *i + 1;
	if (*i == token->len)
		return (1);
	*j = *i;
	while (token->txt[*j] != '*' && *j < token->len)
		*j = *j + 1;
	return (0);
}
