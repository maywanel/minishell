/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:35:36 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:34 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pro_strdup(const char *s)
{
	char	*copy;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	copy = pro_malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len && s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	get_promt_name(t_shell *shell)
{
	char	*last_dir;
	char	buffer[1024];
	char	*tmp;

	tmp = NULL;
	shell->name = NULL;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		last_dir = ft_strrchr(buffer, '/');
		if (last_dir != NULL)
			last_dir++;
		else
			last_dir = buffer;
		free(shell->name);
		tmp = ft_strjoin("\033[0;36m\e[1m", last_dir);
		last_dir = ft_strjoin(tmp, "\e[m\033[0m ");
		free(tmp);
		shell->name = pro_strdup(last_dir);
		free(last_dir);
	}
	else
		perror("getcwd");
}

char	*create_env_string(const char *var, const char *value)
{
	size_t	len;
	char	*result;
	size_t	var_len;
	size_t	val_len;

	if (!var || !value)
		return (NULL);
	var_len = ft_strlen(var);
	val_len = ft_strlen(value);
	len = var_len + 1 + val_len + 1;
	result = pro_malloc(len);
	if (!result)
		return (NULL);
	ft_memcpy(result, var, var_len);
	result[var_len] = '=';
	ft_memcpy(result + var_len + 1, value, val_len);
	result[var_len + 1 + val_len] = '\0';
	return (result);
}

int	get_exit_code(int n)
{
	static int	exit_code = 0;

	if (n >= 0)
		exit_code = n;
	return (exit_code);
}

char	*pro_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = pro_malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	i = -1;
	while (++i < len2)
		result[len1 + i] = s2[i];
	result[len1 + i] = '\0';
	return (result);
}
