/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:03:04 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/23 20:56:09 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirect_error(t_cmd *cmd, int *result)
{
	if (!cmd->cmd[1] && cmd->next
		&& (check_redirect_type(cmd->next) || cmd->next->type == PIPE))
	{
		print_error(cmd->next->cmd[0], 0);
		(*result) = 1;
	}
	else if (!cmd->cmd[1])
	{
		print_error(NULL, 0);
		(*result) = 1;
	}
}
