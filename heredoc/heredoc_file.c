/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 14:40:41 by slee2             #+#    #+#             */
/*   Updated: 2021/08/25 02:28:48 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_heredoc_file(t_heredoc *heredoc)
{
	int		fd;

	fd = open(heredoc->file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

void	set_input_mode(void)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ICANON | ECHO);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

void	set_term(void)
{
	char	*env;

	env = getenv("TERM");
	if (env == NULL)
		env = "xterm";
	tgetent(NULL, env);
}

void	unset_heredoc_file(t_data *data)
{
	int		i;
	char	*file_num;
	char	*file_name;

	i = 0;
	while (i < data->h_idx)
	{
		file_num = ft_itoa(i);
		file_name = ft_strjoin(ft_strdup("./.heredoc_"), file_num);
		unlink(file_name);
		free(file_name);
		free(file_num);
		i++;
	}
}

char	*set_file_name(t_data *data, t_cmd *cmd)
{
	char	*file_num;
	char	*file_name;

	file_num = ft_itoa(data->h_idx++);
	file_name = ft_strjoin(ft_strdup("./.heredoc_"), file_num);
	free(cmd->cmd[0]);
	free(file_num);
	cmd->cmd[0] = ft_strdup(file_name);
	return (file_name);
}
