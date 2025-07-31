/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:02:03 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/31 06:39:59 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_whitespace(char c)
{
	char	*s;

	s = WHITESPACE;
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	is_specialchar(char c)
{
	if (c == '|')
		return ('|');
	else if (c == '<')
		return ('<');
	else if (c == '>')
		return ('>');
	return (0);
}

int	count_insidequotes(char *s, int *saver)
{
	char	c;
	int		i;

	i = 2;
	c = s[*saver];
	*saver = *saver + 1;
	while (s[*saver] != c)
	{
		if (s[*saver] == 0)
		{
			detect_error(SE_QUOTES);
			*saver = *saver - 1;
			break ;
		}
		*saver = *saver + 1;
		i++;
	}
	return (i);
}

int	count_size(char *s, int start)
{
	int	i;

	i = start;
	if (is_specialchar(s[start]) == '|')
		return (1);
	else if (is_specialchar(s[start]) != 0
		&& (is_specialchar(s[start]) == is_specialchar(s[start + 1])))
		return (2);
	else if (is_specialchar(s[start]) != 0)
		return (1);
	while (s[i] && is_specialchar(s[i]) == 0 && is_whitespace(s[i]) == 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
			count_insidequotes(s, &i);
		i++;
	}
	return (i - start);
}

t_token	*split(char *s, int *start)
{
	t_token	*token;
	int		size;

	while (s[*start] && is_whitespace(s[*start]))
		*start = *start + 1;
	size = count_size(s, *start);
	if (size == 0)
		return (NULL);
	token = malloc(sizeof(t_token));
	token->txt = s + *start;
	token->len = size;
	token->type = get_token_type(s + *start);
	token->next = NULL;
	*start = *start + token->len;
	return (token);
}
