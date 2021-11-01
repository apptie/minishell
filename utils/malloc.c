/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:07:25 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/21 02:23:51 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_parser_line(char *s)
{
	char	*result;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (check_special(s, i))
			count++;
		i++;
	}
	result = (char *)malloc(sizeof(char) * (i + 2 * count + 1));
	if (!result)
		print_error_cmd();
	return (result);
}
