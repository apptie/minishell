/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 13:58:28 by slee2             #+#    #+#             */
/*   Updated: 2021/08/22 14:43:22 by slee2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_temp(t_node *node)
{
	int		size;
	t_cmd	*cmd;

	size = 2;
	cmd = cmd_malloc(&size, node);
	return (cmd);
}

void	set_new_cmd(t_cmd *cmd, t_node **node, int *j)
{
	cmd->cmd[(*j)] = ft_strdup((*node)->str);
	cmd->quote[(*j)] = (*node)->quote;
	cmd->type = (*node)->type;
	(*j)++;
	if ((*node)->next)
	{
		(*node) = (*node)->next;
		cmd->cmd[(*j)] = ft_strdup((*node)->str);
		cmd->quote[(*j)] = (*node)->quote;
		(*j)++;
	}
	cmd->cmd[(*j)] = 0;
}

void	add_by_redirect(t_cmd *cmd, t_node **node)
{
	t_cmd	*temp;
	int		j;

	temp = init_temp((*node));
	j = 0;
	set_new_cmd(temp, node, &j);
	while (cmd)
	{
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	cmd->next = temp;
	temp->prev = cmd;
}
