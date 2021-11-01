/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:31:01 by jimikim           #+#    #+#             */
/*   Updated: 2021/07/27 23:37:08 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = dest;
	while (ptr[i])
		i++;
	while (src[j])
		ptr[i++] = src[j++];
	ptr[i] = 0;
	return (dest);
}
