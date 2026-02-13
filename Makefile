# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/10 14:22:25 by clwenhaj          #+#    #+#              #
#    Updated: 2026/02/13 16:51:54 by clwenhaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -f

SRCS = actions.c \
		create_and_join_thread.c \
		error.c \
		init.c \
		parsing.c \
		philosophers.c \
		thread_monitoring.c \
		utils.c

OBJS	= ${SRCS:.c=.o}


all: ${NAME}

${NAME}: ${OBJS} 
	${CC} ${CFLAGS} ${OBJS}  -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
