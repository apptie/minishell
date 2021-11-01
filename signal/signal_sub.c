/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:49:34 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/20 14:41:27 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_slash(int signo)
{
	(void)signo;
	write(1, "Quit: 3\n", 8);
}

void	change_c(int signo)
{
	(void)signo;
	write(1, "\n", 1);
}

void	change_signal(void)
{
	signal(SIGQUIT, change_slash);
	signal(SIGINT, change_c);
}
