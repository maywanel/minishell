/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:02:40 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/28 16:31:10 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_var(char **envp, int idx, const char *var,
		const char *value, int var_len)
{
	int	val_len;

	if (!envp || !var || !value)
		return ;
	free(envp[idx]);
	val_len = var_len + 1 + strlen(value);
	envp[idx] = malloc(val_len + 1);
	if (envp[idx])
	{
		envp[idx] = ft_strjoin(var, "=");
		envp[idx] = ft_strjoin(envp[idx], value);
		if (!envp[idx])
		{
			perror("minishell: export: memory allocation failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		perror("minishell: export: memory allocation failed");
		exit(EXIT_FAILURE);
	}
}

static void	add_env_var(t_shell *shell, const char *var, const char *value,
		int var_len)
{
	int		count;
	int		e;
	int		val_len;
	char	**new_envp;

	count = 0;
	e = 0;
	while (shell->envp && shell->envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return ;
	while (e < count)
	{
		new_envp[e] = shell->envp[e];
		e++;
	}
	val_len = var_len + 1 + ft_strlen(value);
	new_envp[count] = malloc(val_len + 1);
	if (new_envp[count])
	{
		ft_memcpy(new_envp[count], var, var_len);
		new_envp[count][var_len] = '=';
		ft_strlcpy(new_envp[count] + var_len + 1, value, ft_strlen(value) + 1);
	}
	new_envp[count + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
}

static void	export_variable(t_shell *shell, char *arg)
{
	char	*equal_sign;
	int		var_len;
	char	*var;
	char	*value;
	int		idx;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		printf("minishell: export: '%s': not a valid identifier\n", arg);
		return ;
	}
	var_len = equal_sign - arg;
	var = malloc(var_len + 1);
	if (!var)
		return ;
	ft_strlcpy(var, arg, var_len + 1);
	var[var_len] = '\0';
	idx = find_env_var(shell->envp, var, var_len);
	value = equal_sign + 1;
	if (idx >= 0)
		update_env_var(shell->envp, idx, var, value, var_len);
	else
		add_env_var(shell, var, value, var_len);
	free(var);
}

void	handle_export(t_shell *shell, char **cmd)
{
	int	i;
	int	j;

	i = 1;
	if (cmd == NULL || cmd[0] == NULL)
	{
		printf("export: usage: export [name = value] ...]\n");
		return ;
	}
	if (cmd[1] == NULL)
	{
		j = 0;
		while (shell->envp && shell->envp[j])
			printf("%s\n", shell->envp[j++]);
		return ;
	}
	while (cmd[i])
	{
		export_variable(shell, cmd[i]);
		i++;
	}
}
