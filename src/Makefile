NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -I ./libft -I./lexer -I./tokens -I./built-in -I./inc.

SRCS    = main.c lexer/lexer.c lexer/split_mod.c tokens/token.c  signal/signal.c utiles/utiles.c parser/parser.c exec/exec.c \
		  exec/heardoc.c built-in/echo.c built-in/pwd.c built-in/cd.c built-in/export.c built-in/env.c exec/ft_enfant.c \
		  exec/ft_check_path.c built-in/unset.c built-in/unset_utiles.c built-in/export_utiles2.c built-in/export_utiles3.c \
		  utiles/utiles2.c utiles/utiles_main1.c utiles/utiles_main2.c utiles/utiles_main3.c utiles/utiles_main4.c built-in/export_utiles.c \
		  lexer/lexer2.c exec/exec2.c exec/exec3.c exec/bon.c parser/parser2.c exec/free_principal.c exec/exec4.c lexer/split_mod2.c

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
