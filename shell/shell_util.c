/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 23:58:12 by slee2             #+#    #+#             */
/*   Updated: 2021/08/25 14:20:29 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*next_cmd(t_cmd *cmd)
{
	if (cmd)
		cmd = cmd->next;
	while (cmd && cmd->type != CMD)
	{
		cmd = cmd->next;
		if (cmd && cmd->type == CMD)
			cmd = cmd->next;
	}
	return (cmd);
}

char	*set_path(char *s1, char *s2)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(ft_strdup(s1), "/");
	path = ft_strjoin(temp, s2);
	return (path);
}

char	*check_path(char *env, char *cmd)
{
	struct dirent	*item;
	DIR				*folder;
	char			*path;

	path = 0;
	folder = opendir(env);
	if (!folder)
		return (0);
	item = readdir(folder);
	while (item)
	{
		if (ft_strcmp(item->d_name, cmd) == 0)
			path = set_path(env, item->d_name);
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

t_cmd	*set_next_cmd(t_cmd *cmd)
{
	while (cmd && cmd->type > PIPE)
		cmd = cmd->next;
	return (cmd);
}

t_cmd	*set_prev_cmd(t_cmd *cmd)
{
	while (cmd && cmd->type > PIPE)
		cmd = cmd->prev;
	return (cmd);
}
