/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 22:34:00 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/22 02:01:58 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input_sub(t_data *data, char *file_name)
{
	t_global	*global;

	global = get_global();
	data->file_in = open(file_name, O_RDONLY, S_IRWXU);
	if (data->file_in == -1)
	{
		print_error_redirect(strerror(errno), file_name);
		data->check_exec = 1;
		global->exit_status = 1;
		data->is_open = 0;
	}
	dup2(data->file_in, STDIN_FILENO);
}

void	redirect_input(t_data *data, t_cmd *cmd)
{
	struct stat	sb;
	char		*file_name;
	t_global	*global;

	global = get_global();
	fd_close(data->file_in);
	if (cmd->type == INPUT)
		file_name = cmd->cmd[1];
	else if (cmd->type == HEREDOC)
		file_name = cmd->cmd[0];
	if (stat(file_name, &sb) == -1)
	{
		print_error_redirect(strerror(errno), cmd->cmd[1]);
		data->check_exec = 1;
		global->exit_status = 1;
		data->is_open = 0;
		return ;
	}
	redirect_input_sub(data, file_name);
}

void	redirect_output(t_data *data, t_cmd *cmd)
{
	t_global	*global;

	fd_close(data->file_out);
	if (cmd->type == TRUNC)
	{
		data->file_out = open(cmd->cmd[1], \
			O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	}
	else
	{
		data->file_out = open(cmd->cmd[1], \
			O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	}
	if (data->file_out == -1)
	{
		global = get_global();
		global->exit_status = 1;
		print_error(strerror(errno), 2);
		return ;
	}
	dup2(data->file_out, STDOUT_FILENO);
}
