/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:58:57 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/21 03:20:06 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_data *data, t_cmd *cmd)
{
	int	result;

	result = 0;
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		result = builtin_cd(data, cmd);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		result = builtin_export(data, cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		result = builtin_env(data);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		result = builtin_unset(data, cmd);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		result = builtin_pwd(data);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		result = builtin_echo(cmd);
	return (result);
}
