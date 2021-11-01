/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:44:38 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/19 02:59:43 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d_signal(void)
{
	char			*cm;
	char			*ce;
	int				row;
	t_global		*global;

	global = get_global();
	set_input_mode();
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
	get_cursor_row(&row);
	if (row > 0)
		row--;
	tputs(tgoto(cm, 12 + (global->h_flag * 2), row), 1, putchar_tc);
	write(1, "exit\n", 5);
	unlink("./.minishell_history");
	exit(0);
}

void	ctrl_c_handler(int signo)
{
	t_global	*global;

	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	global = get_global();
	global->h_flag = 0;
	global->exit_status = 1;
}

void	ctrl_signal(void)
{
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
}
