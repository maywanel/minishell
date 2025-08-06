/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:09:38 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/06 09:44:35 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens(t_token *token)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = token;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static int	fill_argv(char **argv, t_token *token)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = token;
	while (temp)
	{
		argv[i] = pro_malloc(temp->len + 1);
		if (!argv[i])
			return (0);
		ft_strlcpy(argv[i], temp->txt, temp->len + 1);
		i++;
		temp = temp->next;
	}
	argv[i] = NULL;
	return (1);
}

char	**tokens_to_argv(t_token *token)
{
	int		token_count;
	char	**argv;

	if (!token)
		return (NULL);
	token_count = count_tokens(token);
	argv = pro_malloc(sizeof(char *) * (token_count + 1));
	if (!argv)
		return (NULL);
	if (!fill_argv(argv, token))
		return (NULL);
	return (argv);
}
