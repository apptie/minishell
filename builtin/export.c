/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:14:32 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/21 03:20:27 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_new_size(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	int		result;

	i = 1;
	result = 0;
	while (cmd->cmd[i])
	{
		if (!export_check_valid(cmd->cmd[i][0]))
		{
			j = 0;
			while (data->envp[j])
			{
				if (export_check_equals(data->envp[j], cmd->cmd[i]))
					break ;
				j++;
			}
			if (j == 0 || !data->envp[j])
				result++;
		}
		i++;
	}
	i = 0;
	return (result);
}

char	*export_set_result(char *s1, char *s2)
{
	char	*s1_chr;
	char	*s2_chr;
	char	*result;

	s1_chr = ft_strchr(s1, '=');
	s2_chr = ft_strchr(s2, '=');
	if (!s1_chr)
		result = ft_strdup(s2);
	else if (!s2_chr)
		result = ft_strdup(s1);
	else
		result = ft_strdup(s2);
	s2[0] = 0;
	return (result);
}

void	export_valid_new_sub(char **result, char **new, int size, int *k)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	while (++i < size)
	{
		if (!new[i][0])
			continue ;
		j = i;
		flag = 0;
		while (++j < size)
		{
			if (!new[j][0])
				continue ;
			if (export_check_equals(new[i], new[j]))
			{
				flag = 1;
				result[(*k)++] = export_set_result(new[i], new[j]);
				break ;
			}
		}
		if (!flag)
			result[(*k)++] = ft_strdup(new[i]);
	}
}

char	**export_valid_new(t_data *data, t_cmd *cmd, char **new)
{
	int		i;
	int		k;
	int		size;
	char	**result;

	size = export_new_size(data, cmd) + data->envp_size;
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (0);
	data->envp_size = size;
	i = -1;
	k = 0;
	size = 0;
	while (new[size])
		size++;
	export_valid_new_sub(result, new, size, &k);
	result[k] = 0;
	free_double_malloc(new);
	return (result);
}

int	builtin_export(t_data *data, t_cmd *cmd)
{
	char	**new;
	int		i;

	i = 1;
	while (cmd->cmd[i])
		i++;
	if (i < 2)
		return (export_print(data));
	new = export_init_new(data, cmd, i);
	if (!new)
		print_error_env();
	new = export_valid_new(data, cmd, new);
	if (!new)
		print_error_env();
	free_double_malloc(data->envp);
	data->envp = new;
	return (0);
}
