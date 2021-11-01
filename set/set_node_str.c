/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_node_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 23:45:18 by slee2             #+#    #+#             */
/*   Updated: 2021/08/25 10:07:07 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_node_str_result(char *temp, int j)
{
	char	*result;

	temp[j] = 0;
	result = ft_strdup(temp);
	if (!result)
		print_error_cmd();
	free(temp);
	return (result);
}

int	set_node_str_check(char c, char *s, int *i)
{
	return (c != '\'' && s[*i] == '\\' && (*i)
		&& !(s[*i - 1] && s[*i - 1] == '\\'));
}

void	set_node_str_bslash(int *i, int *j, char *temp, char *s)
{
	int	quote;

	quote = check_quote(s, (*i));
	if (s[*i + 1] && check_quote(s, (*i) + 1) != 0)
		temp[(*j)++] = s[(*i)++];
	else if (s[*i + 1] && check_quote(s, (*i) + 1) == 0)
		temp[(*j)++] = s[1 + (*i)++];
}

void	set_node_str_void(int *i, int *flag)
{
	(*flag) = 1;
	(*i)++;
}

char	*set_node_str(char *s, int *i, int j, int flag)
{
	char	*temp;
	char	c;

	set_node_str_init(s, &temp, &c);
	while (s[*i] && (s[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (s[*i] == '\'' || s[*i] == '\"') && !flag)
			c = s[(*i)++];
		else if (c != ' ' && s[*i] == c && !flag)
			set_node_str_sub(&c, i);
		else if (set_node_str_check(c, s, i))
		{
			if (s[*i + 1])
				set_node_str_bslash(i, &j, temp, s);
			else
				set_node_str_void(i, &flag);
		}
		else if (s[*i])
		{
			flag = 0;
			temp[j++] = s[(*i)++];
		}
	}
	return (set_node_str_result(temp, j));
}
