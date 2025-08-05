/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:47:59 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/05 14:44:49 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	gc_free(t_list **collector)
{
	ft_lstclear(collector, free);
}

void	errorfree(void)
{
	pro_collect(NULL);
	cmd_collect(NULL);
	perror("no more free speace\n");
	exit(1);
}
