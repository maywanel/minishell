/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 04:44:04 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/31 06:34:14 by hamel-yo         ###   ########.fr       */
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
