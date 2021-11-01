/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 14:43:03 by slee2             #+#    #+#             */
/*   Updated: 2021/08/09 14:20:15 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	move_cursor_left(t_heredoc *heredoc)
{
	char	*cm;

	cm = tgetstr("cm", NULL);
	if (heredoc->col == 2)
		return ;
	heredoc->col--;
	tputs(tgoto(cm, heredoc->col, heredoc->row), 1, putchar_tc);
}

void	move_cursor_right(t_heredoc *heredoc)
{
	char	*cm;

	cm = tgetstr("cm", NULL);
	heredoc->col++;
	tputs(tgoto(cm, heredoc->col, heredoc->row), 1, putchar_tc);
}

int	nbr_length(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_row(int *row)
{
	char	buf[255];
	int		a;
	int		i;
	int		result;
	int		temp;

	write(0, "\033[6n", 4);
	result = read(0, buf, 254);
	buf[result] = 0;
	a = 0;
	temp = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*row = ft_atoi(&buf[i]) - 1;
			else
				temp = ft_atoi(&buf[i]);
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}
