/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 23:48:52 by slee2             #+#    #+#             */
/*   Updated: 2021/08/23 18:41:40 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_dollar(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (cmd && cmd->cmd[i])
	{
		if (check_str_dollar(cmd->cmd[i]))
		{
			temp = set_cmd_env(data, cmd->cmd[i]);
			free(cmd->cmd[i]);
			cmd->cmd[i] = temp;
		}
		i++;
	}
}

void	run_cmd(t_data *data, t_cmd *cmd)
{
	t_global	*global;

	if (data->is_run == 0)
		return ;
	replace_dollar(data, cmd);
	global = get_global();
	if (cmd && ft_strcmp(cmd->cmd[0], "exit") == 0 && check_pipe(cmd) == 0)
		global->exit_status = builtin_exit(cmd);
	else if (cmd && check_builtin(cmd->cmd[0]))
		global->exit_status = run_builtin(data, cmd);
	else if (cmd)
		global->exit_status = run_exec(data, cmd);
	fd_close(data->pipe_in);
	fd_close(data->pipe_out);
	data->pipe_in = -1;
	data->pipe_out = -1;
	data->is_run = 0;
}
