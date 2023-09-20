# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 14:40:09 by hcherpre          #+#    #+#              #
#    Updated: 2022/07/28 16:33:19 by benjamin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell

SRCS    = srcs/main.c \
            srcs/args.c \
            srcs/builtins.c \
            srcs/cd.c \
            srcs/cleaning.c \
            srcs/commands.c \
            srcs/dollars_utils.c \
            srcs/echo.c \
            srcs/env.c \
            srcs/err.c \
            srcs/executable.c \
            srcs/execute.c \
            srcs/exit.c \
            srcs/export.c \
            srcs/fd.c \
            srcs/fork.c \
            srcs/heredoc.c \
            srcs/initialize.c \
            srcs/norme.c \
            srcs/parse_utils.c \
            srcs/pipe_creation.c \
            srcs/pipe_exec.c \
            srcs/pipe_utils.c \
            srcs/print.c \
            srcs/prompt.c \
            srcs/pwd.c \
            srcs/quotes_dollars.c \
            srcs/quotes_utils.c \
            srcs/quotes.c \
            srcs/signals.c \
            srcs/token_check.c \
            srcs/token_creation.c \
            srcs/tokenize.c \
            srcs/unset.c \
            srcs/expand_heredoc.c

OBJS    = ${SRCS:.c=.o}

GCC     = gcc #-fsanitize=address -g3

RM      = rm -rf

GFLAGS  = -Wall -Wextra -Werror

LIBFT    =   libft/libft.a

all:         ${NAME}

.c.o:
			${GCC} ${GFLAGS} -c $< -o ${<:.c=.o}

${NAME}:    ${OBJS} ${LIBFT}
			${GCC} ${GFLAGS} ${SRCS} ${LIBFT} -lreadline -o ${NAME}
${LIBFT}:
			make -C libft

clean:
			${RM} ${OBJS}
			make -C libft clean

fclean: clean
			${RM} ${NAME}
			${RM} $(LIBFT)
			${RM} valgrind.txt

re:     fclean all

valgrind: ${NAME}
	@valgrind --suppressions=suppressed_leaks --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --verbose --log-file=valgrind.txt ./minishell
	@vi valgrind.txt

.PHONY: all fclean clean re
