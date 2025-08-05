/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_2dp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:04:44 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/05 14:04:30 by hamel-yo         ###   ########.fr       */
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

	str = malloc (sizeof(char) * (token->len + 1));
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

char	**convert_to_ptr(t_token *token)
{
	int	args_size;
	char	**args;

	args_size = token_size(token);
	args = malloc (sizeof(char **) * (args_size + 1));
	args_size = 0;
	while (token != NULL)
	{
		args[args_size] = cpyftoken(token);
		args_size++;
		token = token->next;
	}
	args[args_size] = NULL;
	return (args);
}
