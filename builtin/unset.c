/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 01:25:14 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/21 03:18:46 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_sub_1(t_cmd *cmd, char *s, int k)
{
	int	result;

	result = 0;
	while (k > 0)
	{
		if (ft_strcmp(s, cmd->cmd[k]) == 0)
		{
			result = 1;
			break ;
		}
		k--;
	}
	return (result);
}

int	unset_sub_2(t_data *data, char *s)
{
	int		j;
	int		result;
	char	**envp_split;

	j = 0;
	result = 0;
	while (data->envp[j])
	{
		envp_split = 0;
		if (ft_strncmp(data->envp[j], s, ft_strlen(s)) == 0)
		{
			envp_split = ft_split(data->envp[j], '=');
			if (ft_strcmp(envp_split[0], s) == 0)
			{
				result = 1;
				free(data->envp[j]);
				data->envp[j] = ft_strdup("");
				free_double_malloc(envp_split);
			}
		}
		j++;
	}
	return (result);
}

char	**unset_sub_3(t_data *data, int count)
{
	char	**new;
	int		i;
	int		j;

	new = (char **)malloc(sizeof(char *) * (data->envp_size - count + 1));
	i = 0;
	j = 0;
	while (new && data->envp[i])
	{
		if (ft_strlen(data->envp[i]) > 0)
		{
			if (ft_strncmp(data->envp[i], "_=", 2) == 0)
			{
				i++;
				data->envp_size--;
				continue ;
			}
			new[j++] = ft_strdup(data->envp[i]);
		}
		i++;
	}
	new[j] = 0;
	free_double_malloc(data->envp);
	data->envp = new;
	return (new);
}

int	builtin_unset(t_data *data, t_cmd *cmd)
{
	int		i;
	int		count;

	i = 0;
	while (cmd->cmd[i])
		i++;
	if (i < 2)
	{
		ft_putstr_fd("minishell: unset: not enough arguments\n", 2);
		return (1);
	}
	count = 0;
	i = 0;
	while (cmd->cmd[++i])
	{
		if (unset_sub_1(cmd, cmd->cmd[i], i - 1))
			continue ;
		count += unset_sub_2(data, cmd->cmd[i]);
	}
	unset_sub_3(data, count);
	if (!data->envp)
		print_error_env();
	data->envp_size -= count;
	return (0);
}
