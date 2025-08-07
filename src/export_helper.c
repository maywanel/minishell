/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:48:09 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/07 14:48:09 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_var(char **envp, int idx, const char *var,
		const char *value)
{
	char	*new_env_string;

	if (!envp || !var || !value)
		return ;
	new_env_string = create_env_string(var, value);
	if (!new_env_string)
	{
		perror("minishell: export: memory allocation failed");
		pro_collect(NULL);
		exit(EXIT_FAILURE);
	}
	envp[idx] = new_env_string;
}

void	copy_existing_env(char **new_envp, char **old_envp, int count)
{
	int	e;

	e = 0;
	while (e < count)
	{
		new_envp[e] = old_envp[e];
		e++;
	}
}

void	add_env_var(t_shell *shell, const char *var, const char *value,
		int var_len)
{
	int		count;
	int		val_len;
	char	**new_envp;

	count = 0;
	while (shell->envp && shell->envp[count])
		count++;
	new_envp = pro_malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return ;
	copy_existing_env(new_envp, shell->envp, count);
	val_len = var_len + 1 + ft_strlen(value);
	new_envp[count] = pro_malloc(val_len + 1);
	if (new_envp[count])
	{
		ft_memcpy(new_envp[count], var, var_len);
		new_envp[count][var_len] = '=';
		ft_strlcpy(new_envp[count] + var_len + 1, value, ft_strlen(value) + 1);
	}
	new_envp[count + 1] = NULL;
	shell->envp = new_envp;
}
