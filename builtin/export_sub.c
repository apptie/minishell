/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 22:30:12 by slee2             #+#    #+#             */
/*   Updated: 2021/08/25 02:03:16 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_check_split(char **s1_split, char **s2_split)
{
	int	flag;

	flag = 0;
	if (!s1_split)
	{
		free_double_malloc(s2_split);
		flag = 1;
	}
	if (!s2_split)
	{
		free_double_malloc(s1_split);
		flag = 1;
	}
	return (flag);
}

int	export_check_equals(char *s1, char *s2)
{
	char	**s1_split;
	char	**s2_split;

	s1_split = ft_split(s1, '=');
	s2_split = ft_split(s2, '=');
	if (export_check_split(s1_split, s2_split))
		return (0);
	if (ft_strlen(s1_split[0]) == ft_strlen(s2_split[0]))
	{
		if (ft_strcmp(s1_split[0], s2_split[0]) == 0)
		{
			free_double_malloc(s1_split);
			free_double_malloc(s2_split);
			return (1);
		}
	}
	free_double_malloc(s1_split);
	free_double_malloc(s2_split);
	return (0);
}

int	export_check_valid(char c)
{
	if (('0' <= c && c <= '9') || c == '=')
		return (1);
	return (0);
}

int	export_print(t_data *data)
{
	int		i;
	char	**envp_split;
	char	*envp_chr;

	envp_split = 0;
	i = 0;
	while (data->envp[i])
	{
		printf("declare -x ");
		envp_split = ft_split(data->envp[i], '=');
		envp_chr = ft_strchr(data->envp[i], '=');
		if (envp_split[1])
			printf("%s=\"%s\"", envp_split[0], envp_split[1]);
		else if (envp_chr)
			printf("%s=\"\"", envp_split[0]);
		else
			printf("%s", envp_split[0]);
		printf("\n");
		free_double_malloc(envp_split);
		i++;
	}
	return (0);
}

char	**export_init_new(t_data *data, t_cmd *cmd, int size)
{
	int		i;
	int		j;
	char	**new;

	new = (char **)malloc(sizeof(char *) * (data->envp_size + size));
	if (!new)
		return (0);
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		new[j++] = ft_strdup(data->envp[i]);
		i++;
	}
	i = 1;
	while (cmd->cmd[i])
	{
		if (export_check_valid(cmd->cmd[i][0]))
			print_error_export(cmd->cmd[i]);
		else
			new[j++] = ft_strdup(cmd->cmd[i]);
		i++;
	}
	new[j] = 0;
	return (new);
}
