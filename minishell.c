/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:04:55 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/23 20:53:53 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_minishell_sub(t_data *data, char **read_line)
{
	ft_putstr_fd(*read_line, data->his_fd);
	ft_putstr_fd("\n", data->his_fd);
	data->his_idx++;
	data->d_int = set_dollar_int(*read_line);
	data->d_idx = 0;
	data->parser = init_parser(data, *read_line);
	set_cmd(data, 0, 0, 0);
}

void	do_minishell(t_data *data, struct termios *term)
{
	char		*read_line;
	int			status;

	read_line = 0;
	while (1)
	{
		do_minishell_set_default(data, term);
		read_line = readline("minishell > ");
		if (!read_line)
			ctrl_d_signal();
		if (ft_strlen(read_line) == 0
			|| check_quote(read_line, ft_strlen(read_line))
			|| check_ignore(read_line)
			|| check_read_line(read_line))
		{
			free(read_line);
			continue ;
		}
		add_history(read_line);
		do_minishell_sub(data, &read_line);
		start_shell(data);
		waitpid(-1, &status, 0);
		do_minishell_free(data, read_line);
	}
}

void	print_start_minishell(void)
{
	char	ascii[2860];
	int		result;
	int		fd;

	fd = open("./.ascii", O_RDONLY);
	result = read(fd, &ascii, 2860);
	write(1, ascii, result);
	close(fd);
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term;
	t_data			*data;
	t_global		*global;

	print_start_minishell();
	data = init_data(envp);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	init_global();
	global = get_global();
	(void)argc;
	(void)argv;
	do_minishell(data, &term);
	tcsetattr(STDIN_FILENO, TCSANOW, &global->org_term);
	unlink("./.minishell_history");
}
