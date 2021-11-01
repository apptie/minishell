# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 20:25:03 by jimikim           #+#    #+#              #
#    Updated: 2021/08/24 23:52:44 by jimikim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = ./include
SRCS = ./libft/ft_isdigit.c \
	   ./libft/ft_putstr_fd.c \
	   ./libft/ft_split.c \
	   ./libft/ft_strchr.c \
	   ./libft/ft_strcmp.c \
	   ./libft/ft_strdup.c \
	   ./libft/ft_strlen.c \
	   ./libft/ft_strncmp.c \
	   ./libft/ft_strstr.c \
	   ./libft/ft_strcat.c \
	   ./libft/ft_strjoin.c \
	   ./libft/ft_strlcpy.c \
	   ./libft/ft_strlcat.c \
	   ./libft/ft_strndup.c \
	   ./libft/ft_atoi.c \
	   ./libft/ft_itoa.c \
	   ./libft/ft_strtrim.c \
	   ./heredoc/heredoc_cursor.c \
	   ./heredoc/heredoc_file.c \
	   ./heredoc/heredoc_key.c \
	   ./heredoc/heredoc_arrow.c \
	   ./heredoc/heredoc_str.c \
	   ./heredoc/heredoc_util.c \
	   ./heredoc/heredoc_sub.c \
	   ./heredoc/heredoc.c \
	   ./builtin/builtin.c \
	   ./builtin/cd.c \
	   ./builtin/cd_sub.c\
	   ./builtin/env.c \
	   ./builtin/export.c \
	   ./builtin/export_sub.c \
	   ./builtin/unset.c \
	   ./builtin/pwd.c \
	   ./builtin/exit.c \
	   ./builtin/echo.c \
	   ./check/check.c \
	   ./check/check_sub.c \
	   ./check/check_sub1.c \
	   ./init/init_data.c \
	   ./init/init_parser.c\
	   ./utils/malloc.c \
	   ./set/set.c \
	   ./set/set_node.c \
	   ./set/set_node_str.c \
	   ./set/set_node_str_sub.c \
	   ./set/set_cmd.c \
	   ./set/set_cmd_util.c \
	   ./set/set_cmd_redirect.c \
	   ./set/set_cmd_check_flag.c \
	   ./set/set_cmd_temp.c \
	   ./set/set_cmd_temp_sub.c \
	   ./set/set_cmd_env.c \
	   ./set/set_cmd_env_sub.c \
	   ./shell/shell.c \
	   ./shell/shell_redirect.c \
	   ./shell/shell_cmd.c \
	   ./shell/shell_exec.c \
	   ./shell/shell_util.c \
	   ./shell/shell_sub.c \
	   ./utils/utils.c \
	   ./utils/free.c \
	   ./signal/signal.c \
	   ./signal/signal_sub.c \
	   ./utils/error.c \
	   ./utils//global.c \
	   ./redirect/redirect.c \
	   ./redirect/redirect_pipe.c \
	   ./utils/fd.c \
	   ./minishell_util.c \
	   ./minishell.c
OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lncurses -lreadline -L ~/.brew/opt/readline/lib

%.o : %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $^ -o $@ -I ~/.brew/opt/readline/include

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean :
	rm -f $(OBJS) $(NAME)

re :
	make fclean
	make all

.PHONY :
	all
	clean
	fclean
	re
