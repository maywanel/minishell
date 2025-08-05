/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_gc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:19:11 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/05 14:46:54 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pro_collect(void *ptr)
{
	static t_list	*collector;
	t_list		*node;

	if (ptr == NULL)
		gc_free(&collector);
	node = ft_lstnew(ptr);
	ft_lstadd_back(&collector, node);
}

void	cmd_collect(void *ptr)
{
	static t_list	*collector;
	t_list		*node;

	if (ptr == NULL)
		gc_free(&collector);
	node = ft_lstnew(ptr);
	ft_lstadd_back(&collector, node);
}

void	*cmd_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		errorfree();
	cmd_collect(ptr);
	return (ptr);
}

void	*pro_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		errorfree();
	pro_collect(ptr);
	return (ptr);
}
