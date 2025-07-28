/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 03:38:29 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/28 06:57:34 by hamel-yo         ###   ########.fr       */
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
	return ("");
}

int	valid_key(char *s)
{
	int	i;

	i = 0;
	while (!ft_isdigit(s[0]) && ex_validchar(s[i]))
		i = i + 1;
	return (i);
}

int	size_of_new_token_txt(char **env, t_token *token)
{
	int	i;
	int	ex_b_size;
	int	size;

	i = 0;
	size = 0;
	while (i < token->len)
	{
		if (token->txt[i] == '$')
		{
			ex_b_size = valid_key(token->txt + i);
			if (ex_b_size == 0)
				size++;
			else
				size = size + strlen(env_get_value(env, token->txt + i, ex_b_size));
			i = i + ex_b_size;
		}
		else if (token->txt[i] == '\'')
			size = size + count_insidequotes(token->txt , &i);
		else
			size++;
		i++;
	}
	return (size);
}



int main (int c, char **av, char **env)
{
	t_token	*token;

	token = get_lexer("$1USRE");
	printf("%d\n", size_of_new_token_txt(env, token));
}
