/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:50:51 by slee2             #+#    #+#             */
/*   Updated: 2021/08/23 20:51:56 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_malloc(int *count, t_node *start)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		print_error_cmd();
	cmd->type = start->type;
	if (TRUNC <= cmd->type && cmd->type <= INPUT && start->next
		&& !(TRUNC <= start->next->type && start->next->type <= PIPE))
		(*count) = 2;
	cmd->cmd = (char **)malloc(sizeof(char *) * ((*count) + 1));
	if (!cmd->cmd)
		print_error_cmd();
	cmd->quote = (int *)malloc(sizeof(int) * (*count));
	if (!cmd->quote)
		print_error_cmd();
	cmd->next = 0;
	cmd->prev = 0;
	return (cmd);
}

t_cmd	*cmd_redirect_malloc(int count, t_node *start)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		print_error_cmd();
	cmd->type = start->type;
	if (TRUNC <= cmd->type && cmd->type <= INPUT)
		count = 2;
	cmd->cmd = (char **)malloc(sizeof(char *) * (count + 1));
	if (!cmd->cmd)
		print_error_cmd();
	cmd->quote = (int *)malloc(sizeof(int) * count);
	if (!cmd->quote)
		print_error_cmd();
	cmd->next = 0;
	cmd->prev = 0;
	return (cmd);
}

void	set_cmd_before(t_data *data, t_cmd **before, t_cmd *cmd)
{
	if (!(*before))
	{
		cmd->prev = 0;
		data->cmd = cmd;
		(*before) = data->cmd;
	}
	else
	{
		cmd->prev = (*before);
		(*before)->next = cmd;
		(*before) = cmd;
	}
}

int	count_cmd_node(t_node *node)
{
	int	count;
	int	temp;

	count = 0;
	while (node && node->type != PIPE)
	{
		count++;
		if (check_type(node->type))
		{
			if (node->next)
				temp = 2;
			else
				temp = 1;
			count -= temp;
		}
		node = node->next;
	}
	return (count);
}

void	set_cmd_init(t_data *data, t_node **node, t_node **start)
{
	(*node) = data->parser->start;
	(*start) = data->parser->start;
}
