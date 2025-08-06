/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_2dp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:04:44 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/06 09:34:13 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_size(t_token *token)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		token = token->next;
		i++;
	}
	return (i);
}

char	*creat_nstr(t_token *token)
{
	int		i;
	int		j;
	char	*str;

	str = pro_malloc (sizeof(char) * (token->len + 1));
	j = 0;
	i = 0;
	while (i < token->len)
	{
		if (token->txt[i] != -1)
		{
			str[j] = token->txt[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

char	*cpyftoken(t_token *token)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < token->len)
	{
		if (token->txt[j] == -1)
			i++;
		j++;
	}
	if (i == 0)
		return (token->txt);
	return (creat_nstr(token));
}
