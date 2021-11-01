/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 23:51:14 by slee2             #+#    #+#             */
/*   Updated: 2021/08/24 23:11:15 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_error_status(char *path)
{
	DIR	*folder;
	int	fd;
	int	result;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putstr_fd(": command not found\n", 2);
	else if (fd == -1 && folder == NULL)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (fd == -1 && folder != NULL)
		ft_putstr_fd(": is a directory\n", 2);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd(": Permission denied\n", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		result = 127;
	else
		result = 126;
	if (folder)
		closedir(folder);
	fd_close(fd);
	return (result);
}

int	run_exec_bin(char *path, t_data *data, t_cmd *cmd)
{
	int		result;
	pid_t	pid;

	result = 0;
	pid = fork();
	if (pid == 0)
	{
		if (ft_strchr(path, '/') != NULL)
			execve(path, cmd->cmd, data->envp);
		result = set_error_status(path);
		exit(result);
	}
	else
		waitpid(pid, &result, 0);
	result /= 256;
	return (result);
}

char	*run_exec_sub_1(char **env_split, t_cmd *cmd)
{
	char	*path;
	int		i;

	path = check_path(env_split[0] + 5, cmd->cmd[0]);
	i = 1;
	while (cmd->cmd[0] && env_split[i] && path == NULL)
		path = check_path(env_split[i++], cmd->cmd[0]);
	free_double_malloc(env_split);
	return (path);
}

int	run_exec_sub_2(t_data *data, t_cmd *cmd, char *path)
{
	int	result;

	result = 127;
	if (path)
		result = run_exec_bin(path, data, cmd);
	else
		result = run_exec_bin(cmd->cmd[0], data, cmd);
	free(path);
	return (result);
}

int	run_exec(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*env;
	char	**env_split;
	char	*path;

	i = 0;
	env = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
			env = data->envp[i];
		i++;
	}
	if (!env)
		return (run_exec_bin(cmd->cmd[0], data, cmd));
	env_split = ft_split(env, ':');
	if (!env_split)
		print_error_cmd();
	if (!cmd->cmd[0] && !env_split[0])
		return (1);
	path = run_exec_sub_1(env_split, cmd);
	return (run_exec_sub_2(data, cmd, path));
}
