# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tliot <tliot@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 21:22:24 by tliot             #+#    #+#              #
#    Updated: 2022/08/03 23:58:10 by tliot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR =       mandatory

SRCS	=	ft_action.c\
			ft_free.c\
			ft_init.c\
			ft_utils.c\
			main.c\


OBJS			=	$(SRCS:%.c=%.o)
OBJSD			=	$(SRCS:%.c=%.d)
NAME			=	philo
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g3 -pthread -MMD


RM				=	rm -f

all:		${NAME}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		
$(NAME):    philo.h $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 


clean:
	${RM} ${OBJS} ${OBJSD} ${OBJSBONUS}

fclean:		clean
		${RM} ${NAME} ${NAME}_bonus

re:			fclean all

.PHONY: 	all clean fclean re