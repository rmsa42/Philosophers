# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/28 14:50:42 by rumachad          #+#    #+#              #
#    Updated: 2023/09/29 17:14:33 by rumachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = src/philo_main.c src/phil_utils.c
OBJS = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror -pthread -I include

%.o:	%.c
		cc ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			ar rcs philo.a ${OBJS}
			cc ${CFLAGS} philo.a -o ${NAME}

all: ${NAME}		

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f philo.a philo

re: fclean all

.SILENT: