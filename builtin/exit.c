/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 11:28:25 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/20 14:17:00 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!('0' <= s[i] && s[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	exit_free(t_data *data)
{
	if (data->is_parent == 1)
		unlink("./.minishell_history");
}

void	exit_size_two_error(t_cmd *cmd)
{
	if (check_exit_str(cmd->cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	exit(ft_atoi(cmd->cmd[1]));
}

int	builtin_exit(t_cmd *cmd)
{
	int			size;

	size = 0;
	if (!cmd->prev && !cmd->next)
		printf("exit\n");
	while (cmd->cmd[size])
		size++;
	if (size == 1)
		exit(0);
	else if (size == 2)
		exit_size_two_error(cmd);
	else if (size > 2)
	{
		if (check_exit_str(cmd->cmd[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
		else
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	return (1);
}
