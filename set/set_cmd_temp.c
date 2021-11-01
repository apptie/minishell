/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_temp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:21:34 by slee2             #+#    #+#             */
/*   Updated: 2021/08/24 23:51:03 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	it_is_quest_mark(char *s, char **result)
{
	t_global	*global;

	global = get_global();
	if (s[0] && s[0] == '?')
	{
		free(*result);
		*result = set_before_exit_code(global->exit_status);
		return (1);
	}
	return (0);
}

char	*set_env_value(t_data *data, char *s)
{
	int		i;
	char	**s_split;
	char	*result;

	i = 0;
	result = 0;
	if (it_is_quest_mark(s, &result))
		return (result);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], s, ft_strlen(s)) == 0)
		{
			s_split = ft_split(data->envp[i], '=');
			result = ft_strdup(s_split[1]);
			free_double_malloc(s_split);
			break ;
		}
		i++;
	}
	return (result);
}

char	*dollar_env(t_data *data, char *divide_clone, char *result, int signal)
{
	char	**divide_dollar;
	char	*add_env;

	divide_dollar = ft_split(divide_clone, - '$');
	if (signal == 1)
		result = set_env_value(data, divide_dollar[0]);
	else if (divide_clone[0] == - '$')
	{
		result = ft_strjoin(result, ":");
		add_env = set_env_value(data, divide_dollar[0]);
		result = ft_strjoin(result, add_env);
		free(add_env);
	}
	else
	{
		result = ft_strjoin(result, ":");
		result = ft_strjoin(result, divide_dollar[0]);
	}
	result = dollar_env_sub(data, divide_dollar, result);
	return (result);
}

void	add_temp(char **divide_clone, char **result, t_data *data)
{
	int	i;

	i = 1;
	while (divide_clone[i])
	{
		*result = dollar_env(data, divide_clone[i], *result, 0);
		i++;
	}
	free_double_malloc(divide_clone);
}

char	*set_cmd_temp(t_data *data, char *s, int idx)
{
	char		*result;
	char		*target;
	char		**divide_clone;
	t_global	*global;

	result = 0;
	target = 0;
	global = get_global();
	if (!data->d_int[data->d_idx++])
		target = ft_strdup(s + idx + 1);
	else
		target = ft_strndup(s + idx + 1, (data->d_int[data->d_idx - 1]));
	divide_clone = ft_split(target, ':');
	result = dollar_env(data, divide_clone[0], result, 1);
	free(target);
	add_temp(divide_clone, &result, data);
	return (result);
}
