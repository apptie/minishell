/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 17:07:02 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/23 18:47:07 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_type(t_cmd *cmd, int type)
{
	if (cmd && cmd->type == type)
		return (1);
	else
		return (0);
}

int	check_pipe(t_cmd *cmd)
{
	while (cmd)
	{
		if (check_cmd_type(cmd, PIPE))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	check_cmd_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)(- '$'))
		{
			if (str[i + 1] && (str[i + 1] == '\"' || str[i + 1] == '\''))
				continue ;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*check_heredoc_eof(char *str)
{
	if (ft_strncmp(str, "<", 1) == 0)
		return (ft_strdup("<"));
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (ft_strdup("<<"));
	else if (ft_strncmp(str, ">", 1) == 0)
		return (ft_strdup(">"));
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (ft_strdup(">>"));
	return (0);
}
