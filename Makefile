NAME = minishell
DIR_SRC = src/
DIR_OBJ = obj/
LIBFT = libft/libft.a
CC = cc 
CFLAGS = -Wall -Wextra -ggdb 
LDFLAGS = -lreadline
RM = rm -f

SRCS =  $(wildcard $(DIR_SRC)*.c) \
		$(wildcard $(DIR_SRC)/builtins/*.c) \

OBJS = $(SRCS:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)

all: $(NAME)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

clean:
	make clean -C libft
	rm -rf $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all