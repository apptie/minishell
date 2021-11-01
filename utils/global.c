/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 21:10:16 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/24 23:08:57 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	*get_global(void)
{
	static t_global	global;

	return (&global);
}

void	init_global(void)
{
	t_global	*global;

	global = get_global();
	global->h_flag = 0;
	global->exit_status = 0;
	tcgetattr(STDIN_FILENO, &global->org_term);
}
