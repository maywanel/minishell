/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:15:35 by moel-mes          #+#    #+#             */
/*   Updated: 2025/08/06 21:18:35 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_sep(char a, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (a == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*add_str(char *str, int size, int k)
{
	int		i;
	char	*new_str;

	new_str = (char *) malloc(size + 1);
	i = 0;
	while (i < size)
	{
		new_str[i] = str[i + k];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	alloc_res(char ***result, char *str, char *charset)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[k])
	{
		j = 0;
		while (!is_sep(str[k + j], charset) && str[k + j])
			j++;
		if (j)
			i++;
		k += j;
		while (str[k] && is_sep(str[k], charset))
			k++;
	}
	if (!*charset)
		i = 1;
	*result = (char **) malloc(sizeof(char *) * (i + 1));
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	int		j;
	int		k;
	char	**result;

	i = 0;
	k = 0;
	alloc_res(&result, str, charset);
	while (str[k])
	{
		j = 0;
		while (!is_sep(str[k + j], charset) && str[k + j])
			j++;
		if (j)
		{
			result[i] = add_str(str, j, k);
			i++;
		}
		k += j;
		while (str[k] && is_sep(str[k], charset))
			k++;
	}
	result[i] = 0;
	return (result);
}
