/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 04:44:04 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/09 08:25:01 by hamel-yo         ###   ########.fr       */
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

int	ex_validchar(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

t_token	*last_token(t_token *token, char **env)
{
	t_token	*tmp;

	ex_token(token, env, 1);
	token = ef_token(token);
	token = get_wild_card(token);
	tmp = token;
	while (tmp)
	{
		tmp->txt = cpyftoken(tmp);
		tmp = tmp->next;
	}
	return (token);
}
