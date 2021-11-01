/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:34:07 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/24 23:10:23 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_malloc(char **target)
{
	int	i;

	i = 0;
	while (target[i])
		free(target[i++]);
	free(target);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	if (!cmd)
		return ;
	while (cmd)
	{
		free_double_malloc(cmd->cmd);
		free(cmd->quote);
		temp = cmd;
		cmd = cmd->next;
		free(temp);
	}
}

void	free_parser(t_parser *parser)
{
	t_node	*node;
	t_node	*temp;

	if (!parser)
		return ;
	node = parser->start;
	if (!node)
	{
		free(parser);
		return ;
	}
	while (node)
	{
		temp = node;
		node = node->next;
		free(temp->str);
		free(temp);
	}
	free(parser);
}

void	free_data(t_data *data)
{
	free_parser(data->parser);
	free_cmd(data->cmd);
	free_double_malloc(data->envp);
	free(data);
}
