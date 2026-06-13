NAME			=	philo

SRCS			=	main.c				\
					utils.c				\
					eat_simulation.c

OBJS			=	$(SRCS:%.c=obj/%.o)

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -pthread

RM				=	rm -f

.PHONY:			all clean fclean re

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

obj/%.o:		%.c
				@mkdir -p obj
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) -r obj

fclean:			clean
				$(RM) $(NAME)

re:				fclean all