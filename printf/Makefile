SRC = ft_printf.c ft_putnbr.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

OBJS = $(SRC:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I ./ -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS) $(OBJSBONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
 	
.PHONY: all clean fclean re bonus