# Makefile for Minishell Project

# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g
#CFLAGS  = -fsanitize=address -g
# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
LIBFTDIR = Libft
LIBFT = $(LIBFTDIR)/libft.a
LIBS    = -lreadline

# Files
SRCS    = $(SRC_DIR)/main.c $(SRC_DIR)/array.c $(SRC_DIR)/signal.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c $(SRC_DIR)/executor.c \
			$(SRC_DIR)/parser_redir.c $(SRC_DIR)/builtins1.c $(SRC_DIR)/builtins2.c $(SRC_DIR)/builtins.c $(SRC_DIR)/redirection.c \
			$(SRC_DIR)/var_expansion.c $(SRC_DIR)/prompt.c $(SRC_DIR)/builtin_utils.c $(SRC_DIR)/var_expansion1.c \
			$(SRC_DIR)/utils.c $(SRC_DIR)/utils_cmd_path.c $(SRC_DIR)/executor1.c $(SRC_DIR)/executor_utils.c
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
NAME    = minishell

# Rules
.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $^ $(LIBFT) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(LIBFT)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
