# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/28 14:50:42 by rumachad          #+#    #+#              #
#    Updated: 2023/11/02 10:55:22 by rumachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = src/philo_main.c src/philo_utils.c src/philo_checks.c \
		src/philo_init.c src/philo_routine.c src/threads.c
OBJS = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -I include

%.o:	%.c
		cc ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			ar rcs philo.a ${OBJS}
			cc ${CFLAGS} philo.a -o ${NAME} -pthread

all: ${NAME}		

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f philo.a philo

re: fclean all
