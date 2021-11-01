/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 23:17:44 by slee2             #+#    #+#             */
/*   Updated: 2021/08/24 23:10:43 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_minishell_free(t_data *data, char *read_line)
{
	free(read_line);
	free_cmd(data->cmd);
	free_parser(data->parser);
	free(data->d_int);
	unset_heredoc_file(data);
}

void	do_minishell_set_default(t_data *data, struct termios *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	ctrl_signal();
	data->check_exec = 0;
}

int	check_read_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
