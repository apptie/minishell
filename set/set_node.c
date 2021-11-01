/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:35:55 by slee2             #+#    #+#             */
/*   Updated: 2021/08/23 18:48:21 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_node_pointer(t_node **before, t_node *now, t_parser *parser)
{
	if (!*before)
	{
		*before = now;
		parser->start = *before;
	}
	else
	{
		(*before)->next = now;
		now->prev = *before;
		*before = (*before)->next;
	}
}

void	set_node_type(t_node *node, int flag, int quote)
{
	if (ft_strcmp(node->str, ">>") == 0 && flag == 0 && quote == 0)
		node->type = APPEND;
	else if (ft_strcmp(node->str, ">") == 0 && flag == 0 && quote == 0)
		node->type = TRUNC;
	else if (ft_strcmp(node->str, "<<") == 0 && flag == 0 && quote == 0)
		node->type = HEREDOC;
	else if (ft_strcmp(node->str, "<") == 0 && flag == 0 && quote == 0)
		node->type = INPUT;
	else if (ft_strcmp(node->str, "|") == 0 && flag == 0 && quote == 0)
		node->type = PIPE;
	else if (node->prev == 0
		|| (PIPE == node->prev->type)
		|| ((node->prev && node->prev->type == ARG)
			&& node->prev->prev
			&& (TRUNC <= node->prev->prev->type
				&& node->prev->prev->type <= INPUT)))
		node->type = CMD;
	else
		node->type = ARG;
}

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		print_error_cmd();
	node->str = 0;
	node->type = 0;
	node->prev = 0;
	node->next = 0;
	node->quote = 0;
	return (node);
}

void	set_node(char *s, t_node **before, t_parser *parser)
{
	t_node	*node;
	int		i;
	int		flag;

	i = 0;
	skip_space(s, &i);
	while (s[i])
	{
		flag = check_special_bslash(s, i);
		node = init_node();
		if (s[i] == '\'')
			node->quote = 2;
		else if (s[i] == '\"')
			node->quote = 1;
		node->str = set_node_str(s, &i, 0, 0);
		set_node_pointer(before, node, parser);
		set_node_type(node, flag, node->quote);
		parser->size++;
		skip_space(s, &i);
	}
}
