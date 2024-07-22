SRCS = ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_isdigit.c ft_strlen.c

OBJS = $(patsubst %.c,%.o, $(SRCS))

NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

objs:
	cc -c $(CFLAGS) $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
