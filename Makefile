SRCS = philo.c events.c events_utils.c utils.c
SRCS_BONUS = philo_bonus.c events.c events_utils.c utils.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = philo
NAME_BONUS = philo_bonus

LIB_FOLDER = libft
LIB_NAME = libft.a
LIB_COMPILE = ft

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)
bonus: $(NAME_BONUS)

$(LIB_FOLDER)/$(LIB_NAME):
	$(MAKE) -C $(LIB_FOLDER)

$(NAME): $(OBJS) $(LIB_FOLDER)/$(LIB_NAME)
	cc $(CFLAGS) $(OBJS) -L$(LIB_FOLDER) -l$(LIB_COMPILE) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIB_FOLDER)/$(LIB_NAME)
	cc $(CFLAGS) $(OBJS_BONUS) -L$(LIB_FOLDER) -l$(LIB_COMPILE) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE) clean -C $(LIB_FOLDER)
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(MAKE) fclean -C $(LIB_FOLDER)
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
