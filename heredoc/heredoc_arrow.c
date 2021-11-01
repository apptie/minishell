/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 22:45:04 by slee2             #+#    #+#             */
/*   Updated: 2021/08/20 23:11:10 by slee2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_input_copy(char *input, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		input[i] = s[i];
		i++;
	}
	input[i] = 0;
}

int	heredoc_left_arrow(t_heredoc *heredoc)
{
	if (heredoc->idx == 0)
		return (0);
	move_cursor_left(heredoc);
	heredoc->idx--;
	return (1);
}

int	heredoc_right_arrow(t_heredoc *heredoc)
{
	if (heredoc->idx == ft_strlen(heredoc->input))
		return (0);
	move_cursor_right(heredoc);
	heredoc->idx++;
	return (1);
}

int	heredoc_up_arrow(t_heredoc *heredoc)
{
	if (heredoc->his_max == heredoc->his_idx)
		heredoc->backup = ft_strdup(heredoc->input);
	if (heredoc->his_idx == 0)
		return (0);
	heredoc->his_idx--;
	heredoc_input_copy(heredoc->input,
		heredoc->his_split[heredoc->his_idx]);
	heredoc->idx = ft_strlen(heredoc->input);
	heredoc->col = heredoc->idx + 2;
	return (1);
}

int	heredoc_down_arrow(t_heredoc *heredoc)
{
	if (heredoc->his_max == heredoc->his_idx)
		return (0);
	heredoc->his_idx++;
	if (heredoc->his_max == heredoc->his_idx)
	{
		heredoc_input_copy(heredoc->input, heredoc->backup);
		free(heredoc->backup);
	}
	else
	{
		heredoc_input_copy(heredoc->input,
			heredoc->his_split[heredoc->his_idx]);
	}
	heredoc->idx = ft_strlen(heredoc->input);
	heredoc->col = heredoc->idx + 2;
	return (1);
}
