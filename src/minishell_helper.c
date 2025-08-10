/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:46:27 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/10 02:14:54 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	get_exit_code(130);
}

static char	*try_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = pro_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		path = pro_strjoin(tmp, cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

char	*find_path(t_shell *shell, char **cmd)
{
	char	*path;
	char	**paths;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		return (pro_strdup(cmd[0]));
	path = ft_getenv(shell, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ":");
	if (!paths)
		return (NULL);
	path = try_path(paths, cmd[0]);
	free_array(paths);
	return (path);
}
