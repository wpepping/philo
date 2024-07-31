SRCS = philo.c events.c mutex.c utils.c utils2.c libft_utils.c

OBJS = $(SRCS:.c=.o)

NAME = philo

CFLAGS = -Wall -Werror -Wextra -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
