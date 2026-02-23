# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/10 14:22:25 by clwenhaj          #+#    #+#              #
#    Updated: 2026/02/23 16:31:32 by clwenhaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes

RM = rm -f

SRCS = srcs/actions.c \
		srcs/create_and_join_thread.c \
		srcs/error.c \
		srcs/init.c \
		srcs/parsing.c \
		srcs/one_philosopher.c \
		srcs/philosophers.c \
		srcs/thread_monitoring.c \
		srcs/utils.c

OBJS	= ${SRCS:.c=.o}

HEADERS = includes/philosophers.h includes/types.h

all: ${NAME}

${NAME}: ${OBJS} 
	${CC} ${CFLAGS} ${OBJS}  -o ${NAME}

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

clean:
	${RM} ${OBJS} 

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
