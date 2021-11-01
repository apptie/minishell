/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 22:24:40 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/19 14:15:50 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_start(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, *s1) == 0)
			break ;
		i++;
		s1++;
	}
	return (i);
}

static int	ft_get_end(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*s;

	len = ft_strlen(s1);
	s = (char *)s1 + len - 1;
	i = 0;
	while (len--)
	{
		if (ft_strchr(set, *s) == 0)
			break ;
		s--;
	}
	return (len + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup((char *)s1));
	start = ft_get_start(s1, set);
	end = ft_get_end(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	result = (char *)malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy(result, s1 + start, end - start + 1);
	return (result);
}
