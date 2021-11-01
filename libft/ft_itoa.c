/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:10:46 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/05 13:30:21 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_size(int n)
{
	unsigned int	nbr;
	size_t			len;

	len = 0;
	if (n < 0)
	{
		len++;
		nbr = n * -1;
	}
	else if (n == 0)
		return (1);
	else
		nbr = n;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static unsigned int	ft_get_nbr(int n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	unsigned char	nbr;
	char			*result;
	size_t			size;

	size = ft_get_size(n);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (0);
	result[size--] = 0;
	nbr = ft_get_nbr(n);
	if (n < 0)
		result[0] = '-';
	else if (n == 0)
	{
		result[0] = '0';
		return (result);
	}
	else
		nbr = n;
	while (nbr != 0)
	{
		result[size--] = '0' + (nbr % 10);
		nbr = nbr / 10;
	}
	return (result);
}
