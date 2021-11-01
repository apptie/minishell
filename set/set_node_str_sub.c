/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_node_str_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:18:21 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/23 15:23:45 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_node_str_temp(char *s)
{
	char	*result;

	result = malloc(ft_strlen(s) + 1);
	if (!result)
		print_error_cmd();
	return (result);
}

void	set_node_str_init(char *s, char **temp, char *c)
{
	(*temp) = set_node_str_temp(s);
	(*c) = ' ';
}

void	set_node_str_sub(char *c, int *i)
{
	(*c) = ' ';
	(*i)++;
}
