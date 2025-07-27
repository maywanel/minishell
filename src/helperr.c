/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:14:04 by moel-mes          #+#    #+#             */
/*   Updated: 2025/07/27 13:17:26 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
