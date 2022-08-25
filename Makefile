SRCS		= 	philo.c \
				time.c \
				parsing.c \
				routine.c

OBJS		= ${SRCS:.c=.o}

NAME		= philo

CC			= gcc

MAKE		= make

RM			= rm -rf

CFLAGS		= -Wall -Wextra -Werror -pthread

$(NAME):	$(OBJS)
			$(CC) ${CFLAGS} -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus