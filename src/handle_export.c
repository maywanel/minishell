/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:02:40 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/06 20:56:55 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_var(char **envp, int idx, const char *var,
		const char *value)
{
	if (!envp || !var || !value)
		return ;
	envp[idx] = create_env_string(var, value);
	if (!envp[idx])
	{
		perror("minishell: export: memory allocation failed");
		pro_collect(NULL);
		exit(EXIT_FAILURE);
	}
}

static void	copy_existing_env(char **new_envp, char **old_envp, int count)
{
	int	e;

	e = 0;
	while (e < count)
	{
		new_envp[e] = old_envp[e];
		e++;
	}
}

static void	add_env_var(t_shell *shell, const char *var, const char *value,
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
		update_env_var(shell->envp, idx, var, value);
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
		fprintf(stderr, "export: usage: export [name = value] ...]\n");
		get_exit_code(1);
		return ;
	}
	if (cmd[1] == NULL)
	{
		j = 0;
		while (shell->envp && shell->envp[j])
			printf("%s\n", shell->envp[j++]);
		get_exit_code(0);
		return ;
	}
	while (cmd[i])
	{
		export_variable(shell, cmd[i]);
		i++;
	}
	get_exit_code(0);
}
