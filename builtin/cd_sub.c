/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 22:02:34 by slee2             #+#    #+#             */
/*   Updated: 2021/08/21 03:28:24 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_set_oldpwd(t_data *data, char *pwd)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "OLDPWD=", 7) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strjoin(ft_strdup("OLDPWD="), pwd);
		}
		i++;
	}
}

void	cd_set_pwd(t_data *data, char *pwd)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PWD=", 4) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strjoin(ft_strdup("PWD="), pwd);
		}
		i++;
	}
}

int	builtin_cd_sub(t_data **data, t_cmd **cmd)
{
	int		result;
	char	*path;
	char	pwd[USHRT_MAX];

	path = set_cd_path(*data, *cmd);
	getcwd(pwd, USHRT_MAX);
	result = chdir(path);
	if (result == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(path);
		return (1);
	}
	cd_set_oldpwd(*data, pwd);
	getcwd(pwd, PATH_MAX);
	cd_set_pwd(*data, pwd);
	free(path);
	return (0);
}
