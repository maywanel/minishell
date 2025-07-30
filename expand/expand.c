/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 03:38:29 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/29 06:17:44 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*env_get_value(char **env, char *str, int size)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], str, size) == 0)
		{
			if (env[i][size] == '=')
				return (env[i] + size + 1);
		}
		i++;
	}
	return (NULL);
}

int	valid_key(char *s)
{
	int	i;

	i = 0;
	while (!ft_isdigit(s[0]) && ex_validchar(s[i]))
		i = i + 1;
	return (i);
}

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
			*size = *size + strlen(str);
	}
	return (ex_b_size);
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
		else if (token->txt[i] == '\'')
			size = size + count_insidequotes(token->txt , &i);
		else
			size++;
		i++;
	}
	return (size);
}

void	ex_cpy_insidedquote(char **env, char *src, char *dest, int *dst_start, int *src_plase)
{
	int	c_quote;
	char	*value;
	int	key_size;

	c_quote = 0;
	while(c_quote < 2)
	{
		if (src[*src_plase] == '\"')
		{
			dest[*dst_start] = '~';
			c_quote++;
		}
		if (src[*src_plase] == '$')
		{
			key_size = valid_key(src + *src_plase + 1);
			if (key_size > 0)
			{
				value = env_get_value(env, src + *src_plase + 1, key_size);
				if (value != NULL)
					*dst_start = *dst_start + ft_strlcpy(dest + *dst_start, value , ft_strlen(value) + 1) - 1;
				*src_plase = *src_plase + key_size;
			}
			else
				dest[*dst_start] = '$';
		}		
		else
			dest[*dst_start] = src[*src_plase];
		*dst_start = *dst_start + 1;
		*src_plase = *src_plase + 1;
	}
	*dst_start = *dst_start - 1;
	*src_plase = *src_plase - 1;
}

void	ex_cpy_insidesquote(char *src, char *dest, int *dst_start, int *src_plase)
{
	int	c_quote;

	c_quote = 0;
	while(c_quote < 2)
	{
		if (src[*src_plase] == '\'')
		{
			dest[*dst_start] = '~';
			c_quote++;
		}
		else
			dest[*dst_start] = src[*src_plase];
		*dst_start = *dst_start + 1;
		*src_plase = *src_plase + 1;
	}
	*dst_start = *dst_start - 1;
	*src_plase = *src_plase - 1;
}

char	*new_token_txt(char **env, char *txt, int len)
{
	char	*new_txt;
	char	*value;
	int		key_size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_txt = malloc(sizeof(char *) *(len + 1));
	while (i < len)
	{
		if (txt[i] == '$')
		{
			key_size = valid_key(txt + i + 1);
			if (key_size > 0)
			{
				value = env_get_value(env, txt + i + 1, key_size);
				if (value != NULL)
					j = j + ft_strlcpy(new_txt + j, value , ft_strlen(value) + 1) - 1;
				i = i + key_size;
			}
			else
				new_txt[j] = '$';
		}
		else if (txt[i] == '\'')
			ex_cpy_insidesquote(txt, new_txt, &j, &i);
		else if (txt[i] == '\"')
			ex_cpy_insidedquote(env, txt, new_txt, &i, &j);
		else
			new_txt[j] = txt[i];
		i++;
		j++;
	}
	new_txt[j] = 0;
	return (new_txt);
}

void	ex_token(t_token *token, char **env)
{
	while (token != NULL)
	{
		token->len = size_of_new_token_txt(env, token);
		if (token->len == 0)
			token->txt = NULL;
		else
			token->txt = new_token_txt(env, token->txt, token->len);
		token = token->next;
	}
}

int main (int c, char **av, char **env)
{
	char *str;
	t_token	*token;
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	while (1)
	{
		str = readline(">>");
		if (str == NULL)
			return(0);
		add_history(str);
		token = get_lexer(str);
		ex_token(token, env);
		while (token != NULL)
		{
			printf("%d ||| %s \n", token->len, token->txt);
			token = token->next;
		}
	}
}
