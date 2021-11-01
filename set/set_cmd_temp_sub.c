/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_temp_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 01:00:58 by slee2             #+#    #+#             */
/*   Updated: 2021/08/21 02:39:16 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_code(int temp, int size, int nbr)
{
	char	*result;

	while (temp)
	{
		temp /= 10;
		size++;
	}
	result = malloc(size + 1);
	if (!result)
		print_error_env();
	result[size] = 0;
	while (nbr)
	{
		result[--size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (result);
}

char	*set_before_exit_code(int nbr)
{
	char	*result;
	int		temp;
	int		size;

	temp = nbr;
	size = 0;
	if (temp == 0)
	{
		result = malloc(2);
		if (!result)
			print_error_env();
		result[0] = '0';
		result[1] = 0;
	}
	else
		result = set_code(temp, size, nbr);
	return (result);
}

char	*dollar_env_sub(t_data *data, char **divide_dollar, char *result)
{
	int		i;
	char	*add_env;

	free(divide_dollar[0]);
	i = 1;
	while (divide_dollar[i])
	{
		add_env = set_env_value(data, divide_dollar[i]);
		result = ft_strjoin(result, add_env);
		free(add_env);
		free(divide_dollar[i]);
		i++;
	}
	free(divide_dollar[i]);
	free(divide_dollar);
	return (result);
}
