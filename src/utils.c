/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:35:36 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/06 11:04:04 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *pro_strdup(const char *s)
{
	char *copy;
	size_t len;
	size_t i;

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
	char	*temp;
	char	*result;

	temp = ft_strjoin(var, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

int get_exit_code(int n)
{
	static int exit_code = 0;
	if (n >= 0)
		exit_code = n;
	return (exit_code);
}
