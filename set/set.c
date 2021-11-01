/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:15:26 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/21 02:17:37 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*set_dollar_int(char *s)
{
	int	*result;
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (check_quote(s, i) != 2 && s[i] == '$')
			count++;
		i++;
	}
	result = malloc(sizeof(int) * count);
	if (!result)
		print_error_env();
	i = 0;
	while (i < count)
		result[i++] = 0;
	return (result);
}
