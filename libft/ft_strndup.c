/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:15:04 by jimikim           #+#    #+#             */
/*   Updated: 2021/07/28 21:38:20 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s1, int size)
{
	char	*result;
	int		i;

	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (0);
	i = 0;
	while (s1[i] && i < size)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = 0;
	return (result);
}
