/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:00:39 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/07 14:00:39 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pwd(void)
{
	char	buffer[1024];
	int		exit_code;

	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		printf("%s\n", buffer);
		exit_code = 0;
	}
	else
	{
		perror("getcwd");
		exit_code = 1;
	}
	return (exit_code);
}

int	handle_env(t_shell *shell)
{
	char	**env;

	if (!shell || !shell->envp)
	{
		ft_putstr_fd("minishell: env: no environment variables set\n", 2);
		return (1);
	}
	env = shell->envp;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
