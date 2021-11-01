/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 20:50:16 by slee2             #+#    #+#             */
/*   Updated: 2021/08/25 00:11:14 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_cmd_bef_aft(char *s, int start, int end)
{
	char		*result;
	int			i;

	if (start >= end)
		return (0);
	result = malloc(end - start + 1);
	if (!result)
		return (0);
	i = 0;
	while (start < end)
		result[i++] = s[start++];
	result[i] = 0;
	return (result);
}

int	case_temp(char *temp, char *before, char *after, char **result)
{
	if (!temp)
	{
		if (before)
		{
			(*result) = ft_strdup(before);
			free(before);
		}
		if (after)
			free(after);
		return (-1);
	}
	return (0);
}

char	*strjoin_and_free(char *result, char *bef_aft)
{
	result = ft_strjoin(result, bef_aft);
	free(bef_aft);
	return (result);
}

int	set_cmd_env_sub(t_data *data, char *s, int i, char **result)
{
	int		j;
	char	*before;
	char	*after;
	char	*temp;

	j = 0;
	before = set_cmd_bef_aft(s, j, i);
	j = i + 1 + data->d_int[data->d_idx];
	after = set_cmd_bef_aft(s, i + 1 + data->d_int[data->d_idx], ft_strlen(s));
	temp = set_cmd_temp(data, s, i);
	if (case_temp(temp, before, after, result))
		return (-1);
	i += data->d_int[data->d_idx - 1];
	if (before)
		(*result) = strjoin_and_free((*result), before);
	(*result) = ft_strjoin((*result), temp);
	if (after && (!s[i + 1] || !check_cmd_str(s + i)))
	{
		(*result) = strjoin_and_free((*result), after);
		free(temp);
		return (-1);
	}
	set_cmd_env_free(after, temp);
	return (i);
}

char	*set_cmd_env(t_data *data, char *s)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	result = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == (char)(- '$'))
		{
			i = set_cmd_env_sub(data, s, i, &result);
			if (i == -1)
				break ;
		}
		i++;
	}
	return (result);
}
