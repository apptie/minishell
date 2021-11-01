/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 14:49:46 by slee2             #+#    #+#             */
/*   Updated: 2021/08/20 23:11:07 by slee2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_backspace(t_heredoc *heredoc)
{
	if (heredoc->col != 2)
		heredoc->col--;
	delete_str(heredoc, heredoc->idx);
	if (heredoc->idx != 0)
		heredoc->idx--;
}

int	heredoc_enter(t_heredoc *heredoc, t_cmd *cmd)
{
	int			len;
	t_global	*global;

	global = get_global();
	len = ft_strlen(heredoc->input);
	if (len == ft_strlen(cmd->cmd[1])
		&& ft_strcmp(heredoc->input, cmd->cmd[1]) == 0)
	{
		write(1, "\n", 1);
		global->exit_status = 0;
		close(heredoc->fd);
		return (0);
	}
	heredoc->input[len] = '\n';
	heredoc->input[len + 1] = 0;
	heredoc->idx = 0;
	heredoc->col = 2;
	heredoc->row++;
	write(1, "\n> ", 3);
	write(heredoc->fd, heredoc->input, ft_strlen(heredoc->input));
	heredoc->input[0] = 0;
	heredoc->his_idx = heredoc->his_max;
	return (1);
}
