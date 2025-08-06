/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:51:27 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/06 10:17:05 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env_var(const char *var, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], var, ft_strlen(var)) == 0
			&& (shell->envp[i][ft_strlen(var)] == '='
			|| shell->envp[i][ft_strlen(var)] == '\0'))
		{
			free(shell->envp[i]);
			while (shell->envp[i])
			{
				shell->envp[i] = shell->envp[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

void	handle_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_env_var(args[i], shell);
		i++;
	}
	get_exit_code(0);
}
