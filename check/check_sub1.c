/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sub1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 17:12:12 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/23 20:42:44 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect_type(t_cmd *cmd)
{
	return ((TRUNC <= cmd->type && cmd->type <= INPUT));
}

int	check_redirect(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (ft_strchr("><", s[len - 1]))
		return (1);
	return (0);
}

int	check_str_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)(- '$'))
			return (1);
		i++;
	}
	return (0);
}

int	check_ignore(char *s)
{
	int	result;
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == ';' || s[i] == '&' || s[i] == '*' || s[i] == '\\'
			|| (s[i] == '|' && s[i + 1] && s[i + 1] == '|'))
		{
			result = check_quote(s, i);
			if (result == 0)
			{
				if (!(s[i] == '\\' && s[i + 1]))
					return (1);
			}
		}
		if (s[i] == '<' || s[i] == '>')
			flag = 1;
		i++;
	}
	if (i != 1 && s[i - 1] == '|' && !flag)
		return (1);
	return (0);
}

int	check_special(char *s, int i)
{
	if (i > 0 && s[i - 1] == '\\' && ft_strchr("><;|", s[i]))
		return (0);
	else if (ft_strchr("><;|", s[i]) && check_quote(s, i) == 0)
		return (1);
	else
		return (0);
}
