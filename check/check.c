/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:54:10 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/23 18:46:11 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quote_sub(int *result, int *flag, int insert)
{
	if (!(*flag))
		(*result) = insert;
	(*flag) = 0;
}

int	check_quote(char *s, int idx)
{
	int	i;
	int	result;
	int	flag;

	i = 0;
	result = 0;
	flag = 0;
	while (s[i] && i != idx)
	{
		if (!flag && s[i] == '\\' && result != 2)
			flag = 1;
		else if (result == 0 && s[i] == '\"')
			check_quote_sub(&result, &flag, 1);
		else if (result == 0 && s[i] == '\'')
			check_quote_sub(&result, &flag, 2);
		else if (result == 1 && s[i] == '\"')
			check_quote_sub(&result, &flag, 0);
		else if (result == 2 && s[i] == '\'')
			check_quote_sub(&result, &flag, 0);
		else if (flag)
			flag = 0;
		i++;
	}
	return (result);
}

int	check_special_bslash(char *s, int i)
{
	if (s[i] && s[i] == '\\' && s[i + 1] && s[i + 1] == ';')
		return (1);
	else if (s[i] && s[i] == '\\' && s[i + 1] && s[i + 1] == '|')
		return (1);
	else if (s[i] && s[i] == '\\' && s[i + 1] && s[i + 1] == '|'
		&& s[i + 2] && s[i + 2] == '|')
		return (1);
	else if (s[i] && s[i] == '\\' && s[i + 1] && s[i + 1] == '>'
		&& s[i + 2] && s[i + 2] == '>')
		return (1);
	else if (s[i] && s[i] == '\\' && s[i + 1] && s[i + 1] == '>')
		return (1);
	else if (s[i] && s[i] == '\\' && s[i + 1] && s[i + 1] == '<'
		&& s[i + 2] && s[i + 2] == '<')
		return (1);
	else if (s[i] && s[i] == '\\' && s[i + 1] && s[i + 1] == '<')
		return (1);
	return (0);
}

int	check_type(int type)
{
	if (type == TRUNC)
		return (1);
	else if (type == APPEND)
		return (1);
	else if (type == HEREDOC)
		return (1);
	else if (type == INPUT)
		return (1);
	else if (type == PIPE)
		return (1);
	else
		return (0);
}

int	check_builtin(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) == 4 && ft_strncmp(str, "echo", 4) == 0)
		return (1);
	else if (ft_strlen(str) == 2 && ft_strncmp(str, "cd", 2) == 0)
		return (1);
	else if (ft_strlen(str) == 3 && ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	else if (ft_strlen(str) == 6 && ft_strncmp(str, "export", 6) == 0)
		return (1);
	else if (ft_strlen(str) == 5 && ft_strncmp(str, "unset", 5) == 0)
		return (1);
	else if (ft_strlen(str) == 3 && ft_strncmp(str, "env", 3) == 0)
		return (1);
	else if (ft_strlen(str) == 4 && ft_strncmp(str, "exit", 4) == 0)
		return (1);
	else
		return (0);
}
