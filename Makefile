NAME			=	philo

SRCS			=	main.c					\
					utils.c					\
					ft_create_destroy.c		\
					ft_atoi_funcs.c			\
					ft_thread_mutex_init.c	\
					ft_time.c				\
					ft_philo_action.c		\

OBJS			=	$(SRCS:%.c=obj/%.o)

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -pthread

RM				=	rm -f


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

.PHONY:			all clean fclean re