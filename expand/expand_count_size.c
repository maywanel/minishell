/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_count_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 06:25:49 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/01 04:03:22 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	should_expand(char **env, char *txt, int *size)
{
	char	*str;
	int		ex_b_size;

	ex_b_size = valid_key(txt);
	if (ex_b_size == 0)
		*size = *size + 1;
	else
	{
		str = env_get_value(env, txt, ex_b_size);
		if (str != NULL)
			*size = *size + ft_strlen(str);
	}
	return (ex_b_size);
}

int	count_insidedquote(char **env, char *s, int *start)
{
	int	size;
	int	c_quotes;

	c_quotes = 0;
	size = 0;
	while (c_quotes < 2)
	{
		if (s[*start] == '\"')
			c_quotes++;
		if (c_quotes == 2)
			return (size);
		if (s[*start] == '$')
			*start = *start + should_expand(env, s + *start + 1, &size);
		size++;
		*start = *start + 1;
	}
	return (size);
}

int	size_of_new_token_txt(char **env, t_token *token)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < token->len)
	{
		if (token->txt[i] == '$')
			i = i + should_expand(env, token->txt + i + 1, &size);
		else if (token->txt[i] == '\"')
			size = size + count_insidedquote(env, token->txt, &i);
		else if (token->txt[i] == '\'')
			size = size + count_insidequotes(token->txt, &i);
		else
			size++;
		i++;
	}
	return (size);
}
