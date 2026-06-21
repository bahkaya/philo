NAME			=	philo

SRCS			=	eat_simulation.c		\
					ft_atoi_funcs.c			\
					ft_create_destroy.c		\
					ft_philo_action.c		\
					ft_thread_mutex_init.c	\
					ft_time.c				\
					main.c					\
					utils.c					

OBJS			=	$(SRCS:%.c=obj/%.o)

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -pthread

RM				=	rm -f


all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
				@echo Object Files Created
				@echo Program Created

obj/%.o:		%.c
				@mkdir -p obj
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@$(RM) -r obj
				@echo Object Files Deleted

fclean:			clean
				@$(RM) $(NAME)
				@echo Program Deleted

re:				fclean all

.PHONY:			all clean fclean re