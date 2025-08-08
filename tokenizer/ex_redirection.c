/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:41:20 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/08 12:12:16 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *ex_redirection(t_token *token, char **env)
{
	t_token	*n_token;

	token->next = NULL;
	n_token = last_token(token, env);
	if (n_token == NULL || n_token->next != NULL)
	{
		get_exit_code(1);
		ft_putstr_fd("minishell: Ambiguous Redirect\n", 2);
		return (NULL);
	}
	return (n_token);
}
