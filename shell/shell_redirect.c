/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 23:43:10 by slee2             #+#    #+#             */
/*   Updated: 2021/08/23 18:48:57 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*move_next_cmd(t_cmd *cmd)
{
	while (cmd && TRUNC <= cmd->type && cmd->type <= PIPE)
		cmd = cmd->next;
	return (cmd);
}

void	prev_redirect(t_data *data, t_cmd *prev)
{
	if (check_cmd_type(prev, TRUNC))
		redirect_output(data, prev);
	else if (check_cmd_type(prev, APPEND))
		redirect_output(data, prev);
	else if (check_cmd_type(prev, INPUT))
		redirect_input(data, prev);
	else if (check_cmd_type(prev, HEREDOC))
		redirect_input(data, prev);
}

void	next_redirect(t_data *data, t_cmd *next, int flag)
{
	if (!flag)
		return ;
	if (check_cmd_type(next, TRUNC))
		redirect_output(data, next);
	else if (check_cmd_type(next, APPEND))
		redirect_output(data, next);
	else if (check_cmd_type(next, INPUT))
		redirect_input(data, next);
	else if (check_cmd_type(next, HEREDOC))
		redirect_input(data, next);
}

void	start_redirect(t_data *data, t_cmd *cmd)
{
	t_cmd	*prev;
	t_cmd	*next;
	int		pipe;
	int		flag;

	prev = set_prev_cmd(cmd);
	next = set_next_cmd(cmd);
	pipe = 0;
	flag = 1;
	if (prev == next)
		flag = 0;
	prev_redirect(data, prev);
	next_redirect(data, next, flag);
	if (prev && prev->type == PIPE)
		pipe = redirect_pipe(data, prev);
	if (next && pipe != 1)
		start_redirect(data, move_next_cmd(next));
	if ((!prev || prev->type <= PIPE)
		&& pipe != 1 && data->check_exec == 0)
	{
		if (cmd && !(TRUNC <= cmd->type && cmd->type <= INPUT))
			run_cmd(data, cmd);
	}
}
