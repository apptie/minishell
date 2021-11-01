/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 12:00:15 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/21 03:07:21 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_cmd *cmd)
{
	int		i;
	int		flag;

	i = 0;
	while (cmd->cmd[i])
		i++;
	if (i < 1)
		return (0);
	i = 1;
	flag = 0;
	while (cmd->cmd[i] && ft_strcmp(cmd->cmd[i], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	while (cmd->cmd[i])
	{
		printf("%s", cmd->cmd[i]);
		if (cmd->cmd[i + 1] && cmd->cmd[i][0])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
