/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_check_flag.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:55:04 by slee2             #+#    #+#             */
/*   Updated: 2021/08/23 18:40:05 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_by_base_cmd(t_node *node, t_cmd *cmd, int i)
{
	cmd->cmd[i] = ft_strdup(node->str);
	cmd->quote[i] = node->quote;
}

t_cmd	*init_cmd_node_size(t_node *node)
{
	int		size;
	t_cmd	*cmd;

	size = count_cmd_node(node);
	cmd = cmd_malloc(&size, node);
	return (cmd);
}

void	set_cmd_flag(t_data *data, t_node **node, t_cmd **before)
{
	t_cmd	*cmd;
	int		i;

	cmd = init_cmd_node_size((*node));
	i = 0;
	while ((*node) && (*node)->type != PIPE)
	{
		if (check_type((*node)->type) != 1)
			add_by_base_cmd((*node), cmd, i++);
		else if (check_type((*node)->type) && (*node)->quote == 0)
			add_by_redirect(cmd, node);
		(*node) = (*node)->next;
	}
	cmd->cmd[i] = 0;
	set_cmd_before(data, before, cmd);
	while (cmd)
	{
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	(*before) = cmd;
}

int	set_cmd_check_flag(t_data *data, t_node **node, t_cmd **before, int flag)
{
	int	result;

	result = 0;
	if (flag)
	{
		set_cmd_flag(data, node, before);
		result = 1;
	}
	return (result);
}
