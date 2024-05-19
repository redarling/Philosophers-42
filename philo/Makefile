SRCS		=	$(addprefix srcs/,utils.c main.c check_input.c \
					actions.c actions_utils.c routine.c)

OBJS		=	${SRCS:.c=.o}

NAME		=	philo

RM			=	rm -f

CC			=	cc

CFLAGS		=  -Wall -Wextra -Werror -Iincludes

all:		${NAME}

${NAME}:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all fclean clean re