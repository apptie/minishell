/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:43:58 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/22 01:59:05 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str, int flag)
{
	char	*s;

	s = str;
	if (flag == 0)
	{
		if (!s)
			s = "newline";
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\'\n", 2);
	}
	else if (flag == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void	print_error_env(void)
{
	ft_putstr_fd("minishell: failed to set environment variables\n", 2);
	exit(1);
}

void	print_error_cmd(void)
{
	ft_putstr_fd("minishell: failed to set command\n", 2);
	exit(1);
}

void	print_error_export(char *s)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	print_error_redirect(char *msg, char *file_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
