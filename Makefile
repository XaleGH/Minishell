NAME = minishell
DIR_SRC = src/
DIR_OBJ = obj/
LIBFT = libft/libft.a
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g -ggdb 
LDFLAGS = -lreadline
RM = rm -f

SRCS =  $(wildcard $(DIR_SRC)*.c) \
		$(wildcard $(DIR_SRC)/builtins/*.c) \
		$(wildcard $(DIR_SRC)/parsing/*.c) \

OBJS = $(SRCS:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)


# Colors
RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[33m
ORANGE = \033[93m
BLUE = \033[94m



all: $(NAME)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(BOLD)$(BLUE)------------------------------------------$(RESET)"
	@echo "$(BOLD)$(RED)🛠️ 🚧        Compilation started       🚧🛠️$(RESET)"
	@echo "\n"
	@echo "$(BOLD)$(ORANGE)⏳      Compilation in progress...      ⏳$(RESET)"
	@make -sC ./libft
	@echo "\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	@echo "$(BOLD)$(GREEN)🎆           Compilation clear          🎆$(RESET)"
	@echo "$(BOLD)$(BLUE)------------------------------------------$(RESET)"

clean:
	@make clean -sC libft
	@rm -rf $(DIR_OBJ)
	@echo "$(BOLD)$(YELLOW)🧹🧼     Cleaned .o Minishell's files  🧼🧹$(RESET)"
	@echo "\n"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC libft
	@echo "$(BOLD)$(YELLOW)🧹🧼      Cleaned Minishell exec       🧼🧹$(RESET)"
	@echo "\n"

re: fclean all