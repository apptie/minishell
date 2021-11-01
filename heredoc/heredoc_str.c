/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 14:53:17 by slee2             #+#    #+#             */
/*   Updated: 2021/08/07 15:15:08 by slee2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_str(t_heredoc *heredoc, int idx)
{
	int	len;

	if (idx == 0)
		return ;
	len = ft_strlen(heredoc->input);
	if (len == idx - 1)
		heredoc->input[len - 1] = 0;
	else
	{
		while (heredoc->input[idx])
		{
			heredoc->input[idx - 1] = heredoc->input[idx];
			idx++;
		}
		heredoc->input[idx - 1] = 0;
	}
}

void	input_str(t_heredoc *heredoc, int idx, int c)
{
	int		len;
	int		i;
	char	*temp;

	len = ft_strlen(heredoc->input);
	if (len == 0)
	{
		heredoc->input[0] = c;
		heredoc->input[1] = 0;
	}
	else if (len == heredoc->idx - 1)
	{
		heredoc->input[idx - 1] = c;
		heredoc->input[idx] = 0;
	}
	else
	{
		temp = ft_strdup(heredoc->input);
		heredoc->input[idx - 1] = c;
		i = idx - 1;
		while (temp[i])
			heredoc->input[idx++] = temp[i++];
		heredoc->input[idx] = 0;
		free(temp);
	}
}

char	write_line(t_heredoc *heredoc)
{
	char	*cm;
	char	*ce;
	int		col;
	int		row;

	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
	col = heredoc->col;
	row = heredoc->row;
	tputs(tgoto(cm, col - heredoc->idx, row), 1, putchar_tc);
	tputs(ce, 1, putchar_tc);
	ft_putstr_fd(heredoc->input, 0);
	tputs(tgoto(cm, col, row), 1, putchar_tc);
	return (0);
}
