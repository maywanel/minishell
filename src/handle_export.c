/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:02:40 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/07 15:05:03 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_without_value(t_shell *shell, char *arg)
{
	int	var_len;
	int	idx;

	var_len = ft_strlen(arg);
	idx = find_env_var(shell->envp, arg, var_len);
	if (idx >= 0)
		return (0);
	add_env_var(shell, arg, "", var_len);
	return (0);
}

static int	export_with_value(t_shell *shell, char *arg, char *equal_sign)
{
	int		var_len;
	char	*var;
	char	*value;
	int		idx;

	var_len = equal_sign - arg;
	var = pro_malloc(var_len + 1);
	if (!var)
		return (1);
	ft_strlcpy(var, arg, var_len + 1);
	var[var_len] = '\0';
	value = equal_sign + 1;
	idx = find_env_var(shell->envp, var, var_len);
	if (idx >= 0)
		update_env_var(shell->envp, idx, var, value);
	else
		add_env_var(shell, var, value, var_len);
	return (0);
}

static int	export_variable(t_shell *shell, char *arg)
{
	char	*equal_sign;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (export_without_value(shell, arg));
	return (export_with_value(shell, arg, equal_sign));
}

int	handle_export(t_shell *shell, char **cmd)
{
	int	i;
	int	j;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (cmd == NULL || cmd[0] == NULL)
		return (ft_putstr_fd("export: usage: export [name = value] ...]\n",
				2), 1);
	if (cmd[1] == NULL)
	{
		j = 0;
		while (shell->envp && shell->envp[j])
		{
			printf("declare -x %s\n", shell->envp[j]);
			j++;
		}
		return (0);
	}
	while (cmd[i])
	{
		exit_code = export_variable(shell, cmd[i]);
		i++;
	}
	return (exit_code);
}
