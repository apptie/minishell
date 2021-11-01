/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:58:16 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/20 22:04:29 by slee2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_cd_path_sub(t_data *data, char *s)
{
	char	*result;
	int		i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "HOME=", 5) == 0)
			break ;
		i++;
	}
	if (!s)
		return (ft_strdup(data->envp[i] + 5));
	result = malloc(ft_strlen(data->envp[i]) - 5 + ft_strlen(s) + 1);
	if (!result)
		exit(1);
	result[0] = 0;
	ft_strcat(result, data->envp[i] + 5);
	ft_strcat(result, s);
	return (result);
}

char	*set_cd_path(t_data *data, t_cmd *cmd)
{
	char	*path;

	if (!cmd->cmd[1])
		path = set_cd_path_sub(data, 0);
	else if (cmd->cmd[1][0] == '~')
		path = set_cd_path_sub(data, cmd->cmd[1] + 1);
	else if (!cmd->cmd[1][0])
		path = set_cd_path_sub(data, 0);
	else
		path = ft_strdup(cmd->cmd[1]);
	return (path);
}

int	builtin_cd(t_data *data, t_cmd *cmd)
{
	int			i;
	char		*path;
	struct stat	sb;

	i = 0;
	if (cmd->prev || cmd->next)
	{
		path = set_cd_path(data, cmd);
		if (stat(path, &sb) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		free(path);
		return (1);
	}
	while (cmd->cmd[i])
		i++;
	if (i > 3)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (builtin_cd_sub(&data, &cmd));
}
