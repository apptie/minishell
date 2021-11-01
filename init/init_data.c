/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:10:14 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/21 02:38:43 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_shlvl(char *s)
{
	char	**s_split;
	int		old_shlvl;
	char	*new_shlvl;
	char	*result;

	s_split = ft_split(s, '=');
	old_shlvl = ft_atoi(s_split[1]);
	new_shlvl = ft_itoa(old_shlvl + 1);
	result = ft_strjoin(ft_strdup(s_split[0]), "=");
	result = ft_strjoin(result, new_shlvl);
	free(new_shlvl);
	free_double_malloc(s_split);
	return (result);
}

char	**set_envp_result(int i)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (!result)
		print_error_env();
	return (result);
}

void	set_envp(t_data *data, char **envp)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	result = set_envp_result(i);
	i = -1;
	j = 0;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			continue ;
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			result[j++] = set_shlvl(envp[i]);
		else
			result[j++] = ft_strdup(envp[i]);
		if (!result)
			print_error_env();
		data->envp_size++;
	}
	result[j] = 0;
	data->envp = result;
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		print_error_env();
	data->envp_size = 0;
	set_envp(data, envp);
	data->d_idx = 0;
	data->d_int = 0;
	data->h_idx = 0;
	data->his_fd = open("./.minishell_history", O_CREAT
			| O_RDWR | O_APPEND, S_IRWXU);
	if (data->his_fd == -1)
		print_error_env();
	data->stdio_in = dup(STDIN_FILENO);
	data->stdio_out = dup(STDOUT_FILENO);
	data->his_idx = 0;
	data->check_exec = 0;
	return (data);
}
