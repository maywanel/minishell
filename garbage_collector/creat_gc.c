/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_gc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:19:11 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/06/10 14:20:50 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	**gc_resizecollecter(int size, void **collector, void *ptr)
{
	int		i;
	void	**new_collector;

	i = 0;
	new_collector = malloc(sizeof(void *) * (size + 2));
	if (new_collector == NULL)
	{
		free(ptr);
		errorfree();
	}
	while (i < size)
	{
		new_collector[i] = collector[i];
		i++;
	}
	new_collector[i] = ptr;
	new_collector[i + 1] = NULL;
	free(collector);
	return (new_collector);
}

void	pro_collect(void *ptr)
{
	void		**save;
	static void	**collector;
	static int	size;

	if (ptr == NULL)
		gc_free(collector);
	size++;
	save = collector;
	collector = malloc(size * sizeof(void *));
	if (collector == NULL)
	{
		free(ptr);
		errorfree();
	}
	collector = gc_resizecollecter(size, collector, ptr);
}

void	cmd_collect(void *ptr)
{
	static void	**collector;
	static int	size;

	if (ptr == NULL)
		gc_free(collector);
	collector = gc_resizecollecter(size, collector, ptr);
	size++;
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
