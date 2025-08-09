/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 07:06:50 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/09 09:15:43 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_heredoc_line(char **env, t_red *red, char *line)
{
	t_token	token;

	if (ft_strchr(red->target, '\"') || ft_strchr(red->target, '\''))
		return (line);
	token.txt = line;
	token.len = ft_strlen(line);
	ex_token(&token, env, 0);
	free(line);
	return (token.txt);
}
