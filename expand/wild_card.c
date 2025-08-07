/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:57:30 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/07 15:09:45 by moel-mes         ###   ########.fr       */
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
	*start = *start - 1;
	return (0);
}

bool	valid_patren(t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < token->len)
	{
		if (token->txt[i] == '*')
			j++;
		if (token->txt[i] == -1)
			if (valid_patren_inquotes(token, &i))
				return (0);
		i++;
	}
	if (j == 0)
		return (0);
	return (1);
}

bool	valid_wild_card(t_token *token, char *n_file)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (n_file[0] == '.' && token->txt[0] != '.')
		return (0);
	while (1)
	{
		while (token->txt[i] == '*' && i < token->len)
			i++;
		if (i == token->len)
			return (1);
		j = i;
		while (token->txt[j] != '*' && j < token->len)
			j++;
		while (n_file[k] != token->txt[i] && n_file[k] != 0)
			k++;
		if (ft_strncmp(token->txt + i, n_file + k, j - i) != 0
			|| (j == token->len && n_file[k + j - i] != 0) || (i == 0
				&& k != 0))
			break ;
		i = j;
	}
	return (0);
}

t_token	*get_files(t_token *token)
{
	DIR				*dir;
	t_token			*files;
	struct dirent	*info;

	dir = opendir(".");
	files = NULL;
	while (1)
	{
		info = readdir(dir);
		if (info == NULL || valid_patren(token) == 0)
			break ;
		if (valid_wild_card(token, info->d_name))
			token_addback(&files, make_token_node(info->d_name));
	}
	closedir(dir);
	return (files);
}

t_token	*get_wild_card(t_token *token)
{
	t_token	*tmp;
	t_token	*new_token;
	t_token	*save_data;

	new_token = NULL;
	while (token != NULL)
	{
		tmp = get_files(token);
		if (tmp == NULL)
		{
			save_data = token->next;
			token->next = NULL;
			token_addback(&new_token, token);
			token = save_data;
		}
		else
		{
			token_addback(&new_token, tmp);
			token = token->next;
		}
	}
	return (new_token);
}
