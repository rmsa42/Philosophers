# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 12:13:08 by rumachad          #+#    #+#              #
#    Updated: 2023/10/20 13:06:13 by rumachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
SRC = src/main.c src/philo_utils_bonus.c src/philo_routine_bonus.c \
		src/philo_checks_bonus.c src/init_bonus.c
OBJS = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -I include

%.o:	%.c
		cc ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			ar rcs philo_bonus.a ${OBJS}
			cc ${CFLAGS} philo_bonus.a -o ${NAME} -lpthread -lrt

all: ${NAME}		

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f philo_bonus.a ${NAME}

re: fclean all