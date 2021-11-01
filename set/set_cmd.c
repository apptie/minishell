/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 20:09:50 by slee2             #+#    #+#             */
/*   Updated: 2021/08/25 01:58:53 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*set_cmd_value(t_node *start, int *count)
{
	t_node	*node;
	t_cmd	*cmd;
	int		i;
	int		j;

	cmd = cmd_malloc(count, start);
	node = start;
	i = 0;
	j = 0;
	while (node && i < (*count))
	{
		cmd->quote[j] = node->quote;
		cmd->cmd[j++] = ft_strdup(node->str);
		i++;
		node = node->next;
	}
	cmd->cmd[j] = 0;
	return (cmd);
}

void	set_cmd_node(t_node **node, t_node **start, int *count)
{
	if ((*node)->next && (*count) > 1
		&& (TRUNC <= (*node)->type && (*node)->type <= INPUT))
	{
		(*start) = (*node)->next->next;
		(*node) = (*node)->next->next;
	}
	else
	{
		(*start) = (*node)->next;
		(*node) = (*node)->next;
	}
	(*count) = 0;
}

void	set_cmd_pipe(t_data *data, t_node **node, t_cmd **before, int *flag)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	cmd = cmd_malloc(&i, (*node));
	cmd->cmd[0] = ft_strdup((*node)->str);
	cmd->cmd[1] = 0;
	cmd->quote[0] = (*node)->quote;
	cmd->type = (*node)->type;
	(*flag) = 0;
	set_cmd_before(data, before, cmd);
	(*node) = (*node)->next;
}

int	set_cmd_check_type(t_data *data, t_node **node, t_cmd **before, int *flag)
{
	int	result;

	result = 0;
	if ((*node)->type == PIPE)
	{
		set_cmd_pipe(data, node, before, flag);
		result = 1;
	}
	else if ((*node)->type == CMD)
		(*flag) = 1;
	return (result);
}

void	set_cmd(t_data *data, int flag, int count, t_cmd *before)
{
	t_node	*node;
	t_cmd	*cmd;
	t_node	*start;

	set_cmd_init(data, &node, &start);
	while (node)
	{
		count++;
		if (set_cmd_check_type(data, &node, &before, &flag))
		{
			start = node;
			continue ;
		}
		if (set_cmd_check_flag(data, &node, &before, flag))
			continue ;
		else if ((check_type(node->type) && node->quote == 0) || !node->next
			|| (check_type(node->next->type) && node->next->quote == 0))
		{
			cmd = set_cmd_value(start, &count);
			set_cmd_before(data, &before, cmd);
			set_cmd_node(&node, &start, &count);
			continue ;
		}
		node = node->next;
	}
}
