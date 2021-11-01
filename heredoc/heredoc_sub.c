/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 14:22:19 by slee2             #+#    #+#             */
/*   Updated: 2021/08/20 23:15:08 by slee2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_input(t_heredoc *heredoc, int c)
{
	heredoc->idx++;
	heredoc->col++;
	input_str(heredoc, heredoc->idx, c);
}

void	set_default(t_heredoc *heredoc)
{
	int	row;

	row = 0;
	get_cursor_row(&row);
	heredoc->row = row;
	heredoc->fd = set_heredoc_file(heredoc);
	write(1, "> ", 2);
}

int	read_heredoc_sub_arrow(t_heredoc *heredoc, int c)
{
	int	flag;

	flag = 0;
	if (c == L_ARROW)
	{
		if (heredoc_left_arrow(heredoc) == 0)
			flag = 1;
	}
	else if (c == R_ARROW)
	{
		if (heredoc_right_arrow(heredoc) == 0)
			flag = 1;
	}
	else if (c == U_ARROW)
	{
		if (heredoc_up_arrow(heredoc) == 0)
			flag = 1;
	}
	else if (c == D_ARROW)
	{
		if (heredoc_down_arrow(heredoc) == 0)
			flag = 1;
	}
	return (flag);
}

int	read_heredoc_sub(t_heredoc *heredoc, int c)
{
	t_global	*global;

	global = get_global();
	if (c == L_ARROW || c == R_ARROW || c == U_ARROW || c == D_ARROW)
	{
		if (read_heredoc_sub_arrow(heredoc, c))
			return (1);
	}
	else if (c == BSPACE)
		heredoc_backspace(heredoc);
	else if (c == CTRL_D)
	{
		if (ft_strlen(heredoc->input) == 0)
		{
			global->exit_status = 0;
			close(heredoc->fd);
			return (2);
		}
		else
			return (1);
	}
	return (0);
}

void	read_heredoc(t_heredoc *h, t_cmd *cmd, int result)
{
	set_default(h);
	while (read(0, &h->c, sizeof(int)))
	{
		if (h->c == L_ARROW || h->c == R_ARROW || h->c == BSPACE
			|| h->c == CTRL_D || h->c == U_ARROW || h->c == D_ARROW)
		{
			result = read_heredoc_sub(h, h->c);
			if (result == 1)
				continue ;
			else if (result == 2)
				break ;
		}
		else if (h->c == ENTER || h->c == R_A_ENTER)
		{
			if (heredoc_enter(h, cmd) == 0)
				break ;
			else
				continue ;
		}
		else
			heredoc_input(h, h->c);
		h->c = write_line(h);
	}
	read_heredoc_exit(result);
}
