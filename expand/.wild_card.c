/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 05:14:32 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/01 11:44:06 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	valid_patren_inquotes(t_token *token, int *start)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (token->txt[*start] == -1)
			i++;
		else if (token->txt[*start] == '*')
			return (1);
		*start = *start + 1;
	}
	return (0);
}

bool	valid_patren(t_token *token)
{
	int		i;
	int		j;
	bool	k;

	i = 0;
	j = 0;
	while (i < token->len)
	{
		if (token->txt[i] == '*')
			j++;
		if (token->txt[i] == -1)
		{
			k = valid_patren_inquotes(token, &i);
			if (k == 1)
				return (0);
		}
		i++;
	}
	if (j == 0)
		return (0);
	return (1);
}

t_token	*get_files(bool hidden)
{
	DIR		*dir;
	t_token		*files;
	struct dirent	*info;

	dir = opendir(".");
	while (1)
	{
		info = readdir(dir);
		if (info == NULL)
			return (tiles);
		if (info->d_type != DT_REG && hidden)
			add_tokenback(&files, make_token_node(info->d_name));
		else
			add_tokenback(&files, make_token_node(info->d_name));
	}
	closedir(dir);
	return (files);
}

