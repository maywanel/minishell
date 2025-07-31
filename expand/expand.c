/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 03:38:29 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/31 08:47:53 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ex_cpy_insidesquote(char *src, char *dest, int *d_s, int *s_p)
{
	int	c_quote;

	c_quote = 0;
	while (c_quote < 2)
	{
		if (src[*s_p] == '\'')
		{
			dest[*d_s] = -1;
			c_quote++;
		}
		else
			dest[*d_s] = src[*s_p];
		*d_s = *d_s + 1;
		*s_p = *s_p + 1;
	}
	*d_s = *d_s - 1;
	*s_p = *s_p - 1;
}

int	replace_value(char **env, char *txt, char *new_txt, int *j)
{
	char	*value;
	int		key_size;

	key_size = valid_key(txt + 1);
	if (key_size == 0)
		new_txt[*j] = '$';
	else
	{
		value = env_get_value(env, txt + 1, key_size);
		if (value != NULL)
			*j = *j + ft_strlcpy(new_txt + *j, value, ft_strlen(value) + 1) - 1;
		else
			*j = *j - 1;
	}
	return (key_size);
}

int	ex_cpy_insidedquote(char **env, char *src, char *dest, int *dst_start)
{
	int	i;
	int	c_quote;

	c_quote = 0;
	i = 0;
	while (c_quote < 2)
	{
		if (src[i] == '\"')
		{
			dest[*dst_start] = -1;
			c_quote++;
		}
		else if (src[i] == '$')
			i = i + replace_value(env, src + i, dest, dst_start);
		else
			dest[*dst_start] = src[i];
		*dst_start = *dst_start + 1;
		i++;
	}
	*dst_start = *dst_start - 1;
	i--;
	return (i);
}

char	*new_token_txt(char **env, t_token *token, int newt_size)
{
	char	*new_txt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_txt = malloc(sizeof(char *) *(newt_size + 1));
	while (i < token->len)
	{
		if (token->txt[i] == '$')
			i = i + replace_value(env, token->txt + i, new_txt, &j);
		else if (token->txt[i] == '\'')
			ex_cpy_insidesquote(token->txt, new_txt, &j, &i);
		else if (token->txt[i] == '\"')
			i = i + ex_cpy_insidedquote(env, token->txt, new_txt, &j);
		else
			new_txt[j] = token->txt[i];
		i++;
		j++;
	}
	new_txt[j] = 0;
	return (new_txt);
}

void	ex_token(t_token *token, char **env)
{
	int	must_expand;
	int	new_token_size;

	must_expand = 0;
	while (token != NULL)
	{
		new_token_size = size_of_new_token_txt(env, token, &must_expand);
		if (new_token_size == 0)
			token->txt = NULL;
		else if (must_expand > 0)
			token->txt = new_token_txt(env, token, new_token_size);
		token->len = new_token_size;
		token = token->next;
	}
}
