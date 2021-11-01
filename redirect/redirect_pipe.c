/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 23:22:33 by slee2             #+#    #+#             */
/*   Updated: 2021/08/21 19:41:07 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->type == CMD)
			return (0);
		cmd = cmd->prev;
	}
	return (1);
}

void	set_redirect_pipe_child(t_data *data)
{
	data->pid = -1;
	data->check_exec = 0;
	data->is_parent = 0;
}

void	set_redirect_pipe_parent(t_data *data, pid_t pid)
{
	data->pid = pid;
	data->is_last = 0;
}

int	redirect_pipe(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		fd_close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		data->pipe_in = pipe_fd[0];
		set_redirect_pipe_child(data);
		return (2);
	}
	else
	{
		fd_close(pipe_fd[0]);
		if (check_pipe_cmd(cmd->prev) || data->is_open == 0)
			fd_close(pipe_fd[1]);
		else
			data->pipe_out = pipe_fd[1];
		dup2(pipe_fd[1], STDOUT_FILENO);
		set_redirect_pipe_parent(data, pid);
		return (1);
	}
}
