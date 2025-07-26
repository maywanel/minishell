/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:58:25 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/28 16:24:22 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strarrlen(char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len])
		len++;
	return (len);
}

int	find_env_var(char **envp, const char *var, int var_len)
{
	int	i;
	int	len;

	i = 0;
	if (!envp || !var || var_len <= 0)
		return (-1);
	while (envp && envp[i])
	{
		len = 0;
		while (envp[i][len] && envp[i][len] != '=')
			len++;
		if (len == var_len && !strncmp(envp[i], var, var_len))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_getenv(t_shell *shell, const char *name)
{
	int		i;
	size_t	len;

	i = 0;
	if (!shell || !shell->envp || !name)
		return (NULL);
	len = 0;
	while (name[len] && name[len] != '=')
		len++;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], name, len)
			&& shell->envp[i][len] == '=')
			return (shell->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	**get_envp(t_shell *shell)
{
	char	**envp;
	int		i;

	if (!shell || !shell->envp)
		return (NULL);
	envp = malloc(sizeof(char *) * (ft_strarrlen(shell->envp) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (shell->envp[i])
	{
		envp[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
