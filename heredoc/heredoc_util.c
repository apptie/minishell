/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 23:13:23 by slee2             #+#    #+#             */
/*   Updated: 2021/08/25 02:35:50 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_error(char *s)
{
	print_error(s, 0);
	exit(1);
}

void	free_heredoc(t_heredoc *heredoc)
{
	free_double_malloc(heredoc->his_split);
	free(heredoc->file_name);
	free(heredoc);
}

int	heredoc_return(int status)
{
	if (status == 0)
		return (0);
	else if (status == 256)
		return (1);
	else
		return (2);
}

void	read_heredoc_exit(int result)
{
	if (result == 2)
		exit(5);
	exit(0);
}
