/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:47:59 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/06/10 14:19:37 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_free(void **collector)
{
	int	i;

	i = 0;
	while (collector[i] != NULL)
	{
		free(collector[i]);
		i++;
	}
	free(collector);
}

void	errorfree()
{
	pro_collect(NULL);
	cmd_collect(NULL);
	perror("no more free speace\n");
	exit(1);
}
