/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 13:51:10 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/24 23:52:28 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <dirent.h>

/*
 * type
 */
# define TRUNC 100
# define APPEND 101
# define HEREDOC 102
# define INPUT 103
# define PIPE 104
# define CMD 107
# define ARG 108

/*
 * termios key
 */
# define L_ARROW 4479771
# define R_ARROW 4414235
# define U_ARROW 4283163
# define D_ARROW 4348699
# define R_A_ENTER 4414218
# define ENTER 10
# define CTRL_D 4
# define BSPACE 127

/*
 * struct
 */
typedef struct s_node		t_node;
typedef struct s_parser		t_parser;
typedef struct s_cmd		t_cmd;
typedef struct s_data		t_data;
typedef struct s_heredoc	t_heredoc;
typedef struct s_global		t_global;

struct	s_node
{
	char	*str;
	int		type;
	int		quote;
	t_node	*prev;
	t_node	*next;
};

struct s_parser
{
	t_node	*start;
	t_node	*end;
	int		size;
};

struct s_cmd
{
	char	**cmd;
	t_node	*node;
	int		type;
	int		*quote;
	t_cmd	*next;
	t_cmd	*prev;
};

struct			s_data
{
	t_parser	*parser;
	t_cmd		*cmd;
	char		**envp;
	int			envp_size;
	int			*d_int;
	int			d_idx;
	int			h_idx;
	int			file_in;
	int			file_out;
	int			his_fd;
	int			his_idx;
	int			check_exec;
	int			pipe_in;
	int			pipe_out;
	int			pid;
	int			stdio_in;
	int			stdio_out;
	int			is_last;
	int			is_parent;
	int			is_pipe;
	int			is_run;
	int			is_open;
};

struct		s_heredoc
{
	char	input[USHRT_MAX];
	char	*file_name;
	int		col;
	int		row;
	int		idx;
	int		fd;
	char	**his_split;
	int		his_idx;
	int		his_max;
	char	*backup;
	int		c;
};

struct		s_global
{
	struct termios	org_term;
	int				h_flag;
	int				exit_status;
};

t_data		*init_data(char **envp);
t_parser	*init_parser(t_data *data, char *read_line);
int			*set_dollar_int(char *s);
void		set_node(char *s, t_node **before, t_parser *parser);
char		*set_node_str(char *s, int *i, int j, int flag);
char		*set_node_str_temp(char *s);
void		set_node_str_init(char *s, char **temp, char *c);
void		set_node_str_sub(char *c, int *i);
void		set_cmd(t_data *data, int flag, int count, t_cmd *before);
void		set_cmd_before(t_data *data, t_cmd **before, t_cmd *cmd);
void		set_cmd_init(t_data *data, t_node **node, t_node **start);
int			set_cmd_check_flag(t_data *data, \
	t_node **node, t_cmd **before, int flag);
t_cmd		*init_cmd_node_size(t_node *node);
int			count_cmd_node(t_node *node);
t_cmd		*cmd_malloc(int *count, t_node *start);
t_cmd		*cmd_redirect_malloc(int count, t_node *start);
void		add_by_redirect(t_cmd *cmd, t_node **node);
char		*set_cmd_env(t_data *data, char *s);
char		*set_cmd_temp(t_data *data, char *s, int idx);
void		set_cmd_env_free(char *after, char *temp);
char		*set_env_value(t_data *data, char *s);
char		*set_before_exit_code(int nbr);
char		*set_before_exit_code(int nbr);
char		*dollar_env_sub(t_data *data, char **divide_dollar, char *result);
int			check_quote(char *s, int idx);
int			check_special(char *s, int i);
int			check_special_bslash(char *s, int i);
int			check_type(int type);
int			check_builtin(char *str);
int			check_cmd_type(t_cmd *cmd, int type);
int			check_pipe(t_cmd *cmd);
int			check_cmd_str(char *str);
char		*check_heredoc_eof(char *str);
int			check_redirect_type(t_cmd *cmd);
int			check_redirect(char *s);
int			check_str_dollar(char *s);
int			check_ignore(char *s);
void		check_redirect_error(t_cmd *cmd, int *result);
char		*malloc_parser_line(char *s);
void		start_shell(t_data *data);
void		start_redirect(t_data *data, t_cmd *cmd);
void		run_cmd(t_data *data, t_cmd *cmd);
int			run_exec(t_data *data, t_cmd *cmd);
t_cmd		*next_cmd(t_cmd *cmd);
char		*set_path(char *s1, char *s2);
char		*check_path(char *env, char *cmd);
t_cmd		*set_next_cmd(t_cmd *cmd);
t_cmd		*set_prev_cmd(t_cmd *cmd);
void		skip_space(char *str, int *i);
int			run_builtin(t_data *data, t_cmd *cmd);
int			builtin_cd(t_data *data, t_cmd *cmd);
int			builtin_cd_sub(t_data **data, t_cmd **cmd);
char		*set_cd_path(t_data *data, t_cmd *cmd);
int			builtin_export(t_data *data, t_cmd *cmd);
int			export_check_split(char **s1_split, char **s2_split);
int			export_check_equals(char *s1, char *s2);
int			export_check_valid(char c);
int			export_print(t_data *data);
char		**export_init_new(t_data *data, t_cmd *cmd, int size);
int			builtin_env(t_data *data);
int			builtin_unset(t_data *data, t_cmd *cmd);
int			builtin_pwd(t_data *data);
int			builtin_exit(t_cmd *cmd);
int			builtin_echo(t_cmd *cmd);
void		ctrl_c_handler(int signo);
void		ctrl_slash_handler(int signo);
void		ctrl_signal(void);
void		ctrl_d_signal(void);
void		change_signal(void);
void		free_double_malloc(char **target);
void		free_cmd(t_cmd *cmd);
void		free_parser(t_parser *parser);
void		free_data(t_data *data);
int			putchar_tc(int tc);
void		move_cursor_left(t_heredoc *heredoc);
void		move_cursor_right(t_heredoc *heredoc);
int			nbr_length(int n);
void		get_cursor_row(int *row);
int			set_heredoc_file(t_heredoc *heredoc);
void		set_input_mode(void);
void		set_term(void);
void		unset_heredoc_file(t_data *data);
char		*set_file_name(t_data *data, t_cmd *cmd);
void		heredoc_backspace(t_heredoc *heredoc);
int			heredoc_enter(t_heredoc *heredoc, t_cmd *cmd);
int			heredoc_left_arrow(t_heredoc *heredoc);
int			heredoc_right_arrow(t_heredoc *heredoc);
int			heredoc_up_arrow(t_heredoc *heredoc);
int			heredoc_down_arrow(t_heredoc *heredoc);
void		delete_str(t_heredoc *heredoc, int idx);
void		input_str(t_heredoc *heredoc, int idx, int c);
char		write_line(t_heredoc *heredoc);
void		heredoc_error(char *s);
void		free_heredoc(t_heredoc *heredoc);
int			heredoc_return(int status);
void		read_heredoc_exit(int result);
void		read_heredoc(t_heredoc *h, t_cmd *cmd, int result);
int			redirect_heredoc(t_data *data, t_cmd *cmd);
void		unset_heredoc_file(t_data *data);
void		print_error(char *str, int flag);
void		print_error_env(void);
void		print_error_cmd(void);
void		print_error_export(char *s);
void		print_error_redirect(char *msg, char *file_name);
void		redirect_input(t_data *data, t_cmd *cmd);
void		redirect_output(t_data *data, t_cmd *cmd);
int			redirect_pipe(t_data *data, t_cmd *cmd);
void		fd_close(int fd);
void		reset_stdio(t_data *data);
void		fds_close(t_data *data);
void		fds_reset(t_data *data);
t_global	*get_global(void);
void		init_global(void);
void		do_minishell_free(t_data *data, char *read_line);
void		do_minishell_set_default(t_data *data, struct termios *term);
int			check_read_line(char *s);

#endif
