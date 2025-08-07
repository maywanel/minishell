/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_gc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:19:11 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/08/07 15:01:47 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pro_collect(void *ptr)
{
	static t_list	*collector;
	static int		number = 0;
	t_list			*node;

	if (ptr == NULL)
		gc_free(&collector, number);
	node = ft_lstnew(ptr);
	number++;
	ft_lstadd_back(&collector, node);
}

void	cmd_collect(void *ptr)
{
	static t_list	*collector;
	static int		number = 0;
	t_list			*node;

	if (ptr == NULL)
		gc_free(&collector, number);
	node = ft_lstnew(ptr);
	number++;
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
