/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:51:02 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/25 13:26:37 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_while_check_error(t_cmd *cmd)
{
	int	result;

	result = 0;
	if (!cmd->prev && cmd->type == PIPE)
	{
		print_error("|", 0);
		result = 1;
	}
	else if (check_redirect_type(cmd))
		check_redirect_error(cmd, &result);
	return (result);
}

int	first_while(t_data *data, t_cmd *cmd)
{
	int	result;

	result = 0;
	while (cmd)
	{
		if (first_while_check_error(cmd))
			return (1);
		if (cmd->cmd[0] && cmd->type == HEREDOC)
		{
			result = redirect_heredoc(data, cmd);
			if (result == 1)
				return (1);
		}
		cmd = cmd->next;
	}
	return (result);
}

t_cmd	*move_cmd_first(t_cmd *cmd)
{
	while (TRUNC <= cmd->type && cmd->type <= PIPE)
	{
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	return (cmd);
}

void	second_while(t_data *data, t_cmd *cmd)
{
	t_global	*global;
	int			status;

	global = get_global();
	while (cmd)
	{
		data->is_last = 1;
		data->is_parent = 1;
		data->is_run = 1;
		data->is_open = 1;
		start_redirect(data, cmd);
		reset_stdio(data);
		fds_close(data);
		fds_reset(data);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (data->is_last == 0)
			global->exit_status = status;
		if (data->is_parent == 0)
			exit(global->exit_status);
		data->check_exec = 0;
		cmd = next_cmd(cmd);
	}
}

void	start_shell(t_data *data)
{
	t_cmd		*cmd;
	t_global	*global;
	int			flag;

	global = get_global();
	flag = first_while(data, data->cmd);
	if (flag == 1)
		return ;
	else if (flag == 2)
		global->h_flag = 1;
	else
		global->h_flag = 0;
	change_signal();
	cmd = move_cmd_first(data->cmd);
	second_while(data, cmd);
}
