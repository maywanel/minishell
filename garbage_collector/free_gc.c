/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:47:59 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/06 20:53:17 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	gc_free(t_list **collector, int number)
{
	t_list	*temp;
	t_list	*next;

	if (!collector || !*collector)
		return ;
	temp = *collector;
	while (temp && number > 0)
	{
		next = temp->next;
		if (temp->content)
			free(temp->content);
		free(temp);
		temp = next;
		number--;
	}
	*collector = temp;
}

void	errorfree(void)
{
	pro_collect(NULL);
	cmd_collect(NULL);
	perror("no more free speace\n");
	exit(1);
}
