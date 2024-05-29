NAME = minishell
DIR_OBJ = obj/
DIR_SRC = src/
DIR_GNL = gnl/
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a
LIBMLX = mlx/libmlx.a
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g -ggdb
RM = rm -rf

SRCS = $(wildcard $(DIR_SRC)*.c) $(wildcard $(DIR_GNL)*.c)
OBJ = $(patsubst $(DIR_SRC)%.c,$(DIR_OBJ)%.o,$(SRCS))

$(NAME): $(OBJ)
		make -C ./printf
		make -C ./libft
		make -C ./mlx
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
		make clean -C libft
		make clean -C printf
		make clean -C mlx
		rm -rf $(DIR_OBJ)

fclean: clean
		$(RM) $(NAME)
		make fclean -C libft
		make fclean -C printf

re: fclean all 