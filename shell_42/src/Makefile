NAME    = Minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS = -fsanitize=address

SRCS    = main.c lexer/lexer.c lexer/split_mod.c tokens/token.c  signal/signal.c
OBJS    = $(SRCS:.c=.o)

LIBFT   = libft/libft.a

LIBS    = -Llibft -lft -lreadline -lncurses

INCLUDES = -Ilibft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
