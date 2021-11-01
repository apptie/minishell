/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:04:31 by jimikim           #+#    #+#             */
/*   Updated: 2021/07/13 23:40:17 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_word(char const *s, char charset)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != charset)
		{
			count++;
			while (*s != charset && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	*ft_set_array(char const *s, int start, int end)
{
	int		i;
	int		j;
	char	*array;

	array = malloc(end - start + 2);
	if (!array)
		return (0);
	i = start;
	j = 0;
	while (i < end)
		array[j++] = s[i++];
	array[j] = 0;
	return (array);
}

void	ft_set_result_sub(int ret_idx, char **ret)
{
	int	free_idx;

	free_idx = 0;
	while (--ret_idx >= 0)
		free(ret[free_idx++]);
	free(ret);
}

void	ft_set_result(char const *s, char c, char **ret, int ret_idx)
{
	int	pos[2];

	pos[0] = 0;
	pos[1] = 0;
	while (s[pos[1]])
	{
		if (s[pos[1]] != c)
		{
			pos[0] = pos[1];
			while (s[pos[1]] != c && s[pos[1]])
				pos[1]++;
			ret[ret_idx++] = ft_set_array(s, pos[0], pos[1]);
			if (!ret[ret_idx - 1])
				ft_set_result_sub(ret_idx, ret);
		}
		else
			pos[1]++;
	}
	ret[ret_idx] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (0);
	result = malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!result)
		return (0);
	ft_set_result(s, c, result, 0);
	return (result);
}
