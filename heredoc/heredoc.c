/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 18:39:00 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/21 02:46:41 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_ctrl_c_handler(int signo)
{
	t_global	*global;

	(void)signo;
	write(1, "\n", 1);
	global = get_global();
	global->exit_status = 1;
	exit(1);
}

t_heredoc	*init_heredoc(t_data *data)
{
	t_heredoc	*heredoc;
	int			fd;
	char		history[USHRT_MAX];
	int			result;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (0);
	heredoc->input[0] = 0;
	heredoc->col = 2;
	heredoc->row = 0;
	heredoc->idx = 0;
	heredoc->fd = 0;
	fd = open("./.minishell_history", O_RDONLY);
	result = read(fd, &history, USHRT_MAX - 1);
	history[result] = 0;
	heredoc->his_split = ft_split(history, '\n');
	heredoc->his_idx = data->his_idx;
	heredoc->his_max = data->his_idx;
	heredoc->c = 0;
	close(fd);
	return (heredoc);
}

int	redirect_heredoc(t_data *data, t_cmd *cmd)
{
	pid_t		pid;
	int			status;
	char		*error;
	t_heredoc	*heredoc;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	heredoc = init_heredoc(data);
	if (!heredoc)
		print_error_cmd();
	heredoc->file_name = set_file_name(data, cmd);
	if (pid == 0)
	{
		error = check_heredoc_eof(cmd->cmd[1]);
		if (error)
			heredoc_error(error);
		set_input_mode();
		set_term();
		signal(SIGINT, here_doc_ctrl_c_handler);
		read_heredoc(heredoc, cmd, 0);
	}
	free_heredoc(heredoc);
	status = 0;
	wait(&status);
	return (heredoc_return(status));
}
