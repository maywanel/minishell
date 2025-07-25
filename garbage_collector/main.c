/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:08:32 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/06/10 14:03:14 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishellh.h"

int	main(int c, char **av, char **env)
{
	int	i;
	char	*s = "hamel-yo$" ;
	char	*str ;
	char	**s_cl;

	while (1)
	{
		str = readline(s);
		cmd_collect(str);
		if (str == NULL)
			break ;
	}
}
