/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 20:16:44 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/14 01:03:22 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_stdio(t_data *data)
{
	dup2(data->stdio_in, STDIN_FILENO);
	dup2(data->stdio_out, STDOUT_FILENO);
}

void	fds_close(t_data *data)
{
	fd_close(data->file_in);
	fd_close(data->file_out);
	fd_close(data->pipe_in);
	fd_close(data->pipe_in);
}

void	fds_reset(t_data *data)
{
	data->file_in = -1;
	data->file_out = -1;
	data->pipe_in = -1;
	data->pipe_out = -1;
	data->pid = -1;
}
